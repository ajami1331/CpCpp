#ifndef validator_h
#define validator_h 1

#include <cstdio>
#include <fstream>
#include <iostream>
#include "solution.h"
#include "utils.h"

namespace validator
{
bool compareFiles(const std::string &p1, const std::string &p2)
{
    std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
    std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        return false; // file problem
    }

    if (f1.tellg() != f2.tellg())
    {
        return false; // size mismatch
    }

    // seek back to beginning and use std::equal to compare contents
    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()), std::istreambuf_iterator<char>(),
                      std::istreambuf_iterator<char>(f2.rdbuf()));
}

void red(FILE *file)
{
    fprintf(file, "\033[1;31m");
}

void green(FILE *file)
{
    fprintf(file, "\033[1;32m");
}

void reset(FILE *file)
{
    fprintf(file, "\033[0m");
}

void Process()
{
    std::ifstream testCaseCntFile;
    std::string testCaseDir(TEST_CASES_DIR);
    testCaseCntFile.open(testCaseDir + "cnt");
    int testCaseCnt = 0;
    testCaseCntFile >> testCaseCnt;
    testCaseCntFile.close();
    std::ofstream outfile;
    outfile.open(OUTPUT_FILE);
    int passedCnt = 0;
    double totalRuntime = 0;
    for (int testCase = 1; testCase <= testCaseCnt; testCase++)
    {
        std::string inputFileForTestcaseName = testCaseDir + std::to_string(testCase) + ".in";
        std::string outputFileForTestcaseName = testCaseDir + std::to_string(testCase) + ".out";
        std::string validFileForTestcaseName = testCaseDir + std::to_string(testCase) + ".val";
        freopen(inputFileForTestcaseName.c_str(), "r", stdin);
        freopen(outputFileForTestcaseName.c_str(), "w", stdout);
        const clock_t tStart = clock();
        solution::Solve();
        totalRuntime = static_cast<double>(clock() - tStart) / CLOCKS_PER_SEC;
        fflush(stdout);
        std::ifstream outputFileForTestcase(outputFileForTestcaseName);
        std::string outputLine;
        while (std::getline(outputFileForTestcase, outputLine))
        {
            outfile << outputLine << std::endl;
            std::cerr << outputLine << std::endl;
        }
        bool success = compareFiles(validFileForTestcaseName, outputFileForTestcaseName);
        if (success)
        {
            passedCnt++;
            green(stderr);
            std::cerr << "Test " << testCase << ": success!" << std::endl;
        }
        else
        {
            red(stderr);
            std::cerr << "Test " << testCase << ": fail!" << std::endl;
        }
        reset(stderr);
    }
    if (passedCnt == testCaseCnt)
    {
        green(stderr);
    }
    else
    {
        red(stderr);
    }
    std::cerr << passedCnt << "/" << testCaseCnt << " test passed!" << std::endl;
    reset(stderr);
    outfile.close();
    fprintf(stderr, "\n>> Avg Runtime: %.10fs\n", totalRuntime / testCaseCnt);
    utils::CreateFileForSubmission();
}

} // namespace validator
#endif