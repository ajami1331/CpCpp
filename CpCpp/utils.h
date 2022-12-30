#ifndef util_h
#define util_h 1

#include <fstream>
#include <iostream>
#include <map>
#include <string>

const int MAX_PATH = 256;

namespace utils
{
    const char* header = "#include ";
    const char* prefix = "#include \"";
    const int prefixLen = strlen(prefix);
    const char* startFile = "main.cc";
    std::map<std::string, bool> visited;
    std::string headers;
    std::string content;

    std::string GetFileName(const std::string& cs)
    {
        std::string fileName;
        for (int i = static_cast<int>(cs.size()) - 1; i >= 0; i--)
        {
            if (cs[i] == '/')
            {
                break;
            }
            fileName.push_back(cs[i]);
        }
        reverse(fileName.begin(), fileName.end());
        return fileName;
    }

    void Process(std::string path, std::string file)
    {
        std::string fullFilePath = path + file;
        if (visited[fullFilePath])
        {
            return;
        }

        visited[fullFilePath] = true;
        std::ifstream fstream(fullFilePath);
        std::string line;
        std::string skippedContent;
        char a, b, c;
        a = fstream.get();
        b = fstream.get();
        c = fstream.get();
        if (a != static_cast<char>(0xEF) || b != static_cast<char>(0xBB) || c != static_cast<char>(0xBF)) {
            fstream.seekg(0);
        }
        else
        {
            std::cerr << "Warning: " + fullFilePath + " contains the so-called 'UTF-8 signature'\n";
        }
        while (std::getline(fstream, line))
        {
            if (line.rfind(prefix) == 0)
            {
                std::string includePath = line.substr(prefixLen);
                includePath.pop_back();
                std::string fileName = GetFileName(includePath);
                std::string dir = includePath.substr(0, includePath.size() - fileName.size());
                Process(path + dir, fileName);
            }
            else if (line.rfind(header) == 0)
            {
                headers.append(line + "\n");
            }
            else
            {
                skippedContent.append(line + "\n");
            }
        }

        content.append(skippedContent);
        fstream.close();
    }

    void CreateFileForSubmission()
    {
        visited.clear();
        visited["utils.h"] = true;
        content.clear();
        Process("", startFile);
        std::ofstream out("submission.cpp");
        out << headers;
        out << content;
        out.close();
    }
}
#endif