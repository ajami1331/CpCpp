#ifndef util_h
#define util_h 1

#include <cstring>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <source_location>
#include <filesystem>
#include "library/StringUtils.h"
#include <cassert>

const int MAX_PATH = 256;

namespace utils
{
    const char* header = "#include";
    const std::string ifPrefix = "#ifdef CLown1331";
    const std::string ifnPrefix = "#ifndef CLown1331";
    const std::string elifPrefix = "#elif";
    const std::string elsePrefix = "#else";
    const std::string endifPrefix = "#endif";
    const bool shouldSkipComment = true;
    std::map<std::string, bool> visited;
    std::vector<std::string> headers;
    std::string content;

    void Process(std::filesystem::path filePath);

    bool IsComment(std::string line)
    {
        library::trim(line);
        return line.rfind("//") == 0;
    }

    void ProcessIncludes(std::string line, std::filesystem::path filePath)
    {
        auto tokens = library::split(line, ' ');
        auto tokensFiltered = std::vector<std::string>{};
        std::copy_if(begin(tokens), end(tokens), back_inserter(tokensFiltered), [](const std::string& s) -> bool {
            return !s.empty();
            });
        assert(tokensFiltered.size() == 2 && "Should be in format {#include $library_name}");
        if (tokensFiltered[1][0] == '<')
        {
            headers.emplace_back(tokensFiltered[0] + " " + tokensFiltered[1] + "\n");
            return;
        }
        std::string includePath = tokensFiltered[1];
        includePath.pop_back();
        includePath.erase(0, 1);
        std::filesystem::path fpath = includePath;
        Process(std::filesystem::path(filePath).remove_filename().concat(fpath.string()));
    }

    std::ifstream OpenInputAndValidate(std::string filePathString)
    {
        std::ifstream fstream(filePathString);
        char a, b, c;
        a = fstream.get();
        b = fstream.get();
        c = fstream.get();
        if (a != static_cast<char>(0xEF) || b != static_cast<char>(0xBB) || c != static_cast<char>(0xBF)) {
            fstream.seekg(0);
        }
        else
        {
            std::cerr << "Warning: " + filePathString + " contains the so-called 'UTF-8 signature'\n";
        }

        return fstream;
    }

    void Process(std::filesystem::path filePath)
    {
        bool skipIfBlock = false;
        auto filePathString = filePath.string();
        if (visited[filePathString])
        {
            return;
        }

        visited[filePathString] = true;
        std::ifstream fstream = OpenInputAndValidate(filePathString);
        std::string line;
        std::string skippedContent;
        while (std::getline(fstream, line))
        {
            library::rtrim(line);
            if (library::trim_n(line).rfind(header) == 0)
            {
                ProcessIncludes(line, filePath);
                continue;
            }

            bool skip = false;

            if (line.empty())
            {
                skip = true;
            }

            if (IsComment(line)) 
            {
                skip = shouldSkipComment;
            }

            if (!library::trim_n(line).rfind(ifPrefix))
            {
                skipIfBlock = true;
            }

            if (skipIfBlock && 
                (!library::trim_n(line).rfind(endifPrefix) 
                || !library::trim_n(line).rfind(elsePrefix) 
                || !library::trim_n(line).rfind(elifPrefix)))
            {
                skip = true;
                if(!library::trim_n(line).rfind(elsePrefix))
                {
                    skippedContent.append(ifnPrefix + "\n");
                }
                else 
                {
                    skippedContent.append("#" + library::trim_n(line).erase(0, 3) + "\n");
                }
                skipIfBlock = false;
            }

            if (skipIfBlock)
            {
                skip = true;
            }

            if (skip)
            {
                continue;
            }
            
            skippedContent.append(line + "\n");
        }

        content.append(skippedContent);
        fstream.close();
    }

    void WriteFile(std::filesystem::path path)
    {
        std::ofstream out(std::filesystem::path(path).remove_filename().concat("submission.cpp"));
        std::sort(headers.begin(), headers.end());
        headers.resize(std::unique(headers.begin(), headers.end()) - headers.begin());
        for (const auto& header : headers)
        {
            out << header;
        }
        out << content;
        out.close();
    }

    void CreateFileForSubmission(const std::source_location location = std::source_location::current())
    {
        auto path = std::filesystem::path(location.file_name());
        visited.clear();
        visited[std::filesystem::path(path).remove_filename().concat("utils.h").string()] = true;
        content.clear();
        Process(path);
        WriteFile(path);
    }
}
#endif