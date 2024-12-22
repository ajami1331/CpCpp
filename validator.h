#ifndef validator_h
#define validator_h 1

#include "library/Common.h"
#include "library/TeeBuf.h"
#include "solution.h"
#include "utils.h"
extern FILE *local_foutput;

namespace validator
{
bool compareFiles(const string &p1, const string &p2)
{
    ifstream f1(p1, ifstream::binary | ifstream::ate);
    ifstream f2(p2, ifstream::binary | ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        return false; // file problem
    }

    if (f1.tellg() != f2.tellg())
    {
        return false; // size mismatch
    }

    // seek back to beginning and use equal to compare contents
    f1.seekg(0, ifstream::beg);
    f2.seekg(0, ifstream::beg);
    return equal(istreambuf_iterator<char>(f1.rdbuf()), istreambuf_iterator<char>(),
                 istreambuf_iterator<char>(f2.rdbuf()));
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

void Process(bool validateTestCases)
{
    if (!validateTestCases)
    {
        freopen(INPUT_FILE, "r", stdin);
        freopen(OUTPUT_FILE, "w", stdout);
        solution::solve();
        fflush(stdout);
        ifstream outputFileForTestcase(OUTPUT_FILE);
        string outputLine;
        while (getline(outputFileForTestcase, outputLine))
        {
            cerr << outputLine << endl;
        }
        return;
    }

    ifstream testCaseCntFile;
    string testCaseDir(TEST_CASES_DIR);
    testCaseCntFile.open(testCaseDir + "cnt");
    int testCaseCnt = 0;
    testCaseCntFile >> testCaseCnt;
    testCaseCntFile.close();
    ofstream outfile;
    outfile.open(OUTPUT_FILE);
    int passedCnt = 0;
    double totalRuntime = 0;
    for (int testCase = 1; testCase <= testCaseCnt; testCase++)
    {
        string inputFileForTestcaseName = testCaseDir + to_string(testCase) + ".in";
        string outputFileForTestcaseName = testCaseDir + to_string(testCase) + ".out";
        string validFileForTestcaseName = testCaseDir + to_string(testCase) + ".val";
        std::ofstream outfileForTestcase(outputFileForTestcaseName);
        TeeBuf teeBuf(cout.rdbuf(), outfileForTestcase.rdbuf());
        cout.rdbuf(&teeBuf);
        freopen(inputFileForTestcaseName.c_str(), "r", stdin);
        local_foutput = fopen(outputFileForTestcaseName.c_str(), "w");
        const clock_t tStart = clock();
        solution::solve();
        totalRuntime += static_cast<double>(clock() - tStart) / CLOCKS_PER_SEC;
        fclose(local_foutput);
        ifstream outputFileForTestcase(outputFileForTestcaseName);
        string outputLine;
        while (getline(outputFileForTestcase, outputLine))
        {
            outfile << outputLine << endl;
        }

        bool success = compareFiles(validFileForTestcaseName, outputFileForTestcaseName);
        if (success)
        {
            passedCnt++;
            green(stderr);
            cerr << "Test " << testCase << ": Success!" << endl;
        }
        else
        {
            red(stderr);
            cerr << "Test " << testCase << ": Fail!" << endl;
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
    cerr << passedCnt << "/" << testCaseCnt << " Test passed!" << endl;
    reset(stderr);

    outfile.close();
    fprintf(stderr, "\n>> Avg Runtime: %.10fs\n", totalRuntime / testCaseCnt);
    utils::CreateFileForSubmission();
}

} // namespace validator
#endif