#ifndef util_h
#define util_h 1

#include <fstream>
#include <iostream>
#include <map>
#include <string>

const int MAX_PATH = 256;

namespace utils
{
    const char* prefix = "#include \"";
    const int prefixLen = strlen(prefix);
    const char* startFile = "main.cpp";
    std::map<std::string, bool> visited;
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
        std::ifstream fstream((fullFilePath));
        std::string line;
        std::string skippedContent;
        while (std::getline(fstream, line))
        {
            if (line.rfind(prefix) == 0)
            {
                std::string includePath = line.substr(prefixLen);
                includePath.pop_back();
                std::string fileName = GetFileName(includePath);
                std::string dir = includePath.substr(0,includePath.size() - fileName.size());
                Process(path + dir, fileName);
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
        std::ofstream out("submission.cc");
        out << content;
        out.close();
    }
}
#endif
