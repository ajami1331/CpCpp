#define _CRT_SECURE_NO_WARNINGS

#include "solution.h"
#include "validator.h"

int main(int argc, char *argv[])
{
#ifdef CLown1331
    validator::Process(true);
    return 0;
#endif
    solution::Solve();
    return 0;
}