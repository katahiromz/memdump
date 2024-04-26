// memdump.cpp --- C++11 memory dumper
#include "memdump.h"
#include <cstdio>
#include <string>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::puts("Usage: memdump <file>");
        return 0;
    }

    FILE *fp = std::fopen(argv[1], "rb");
    if (!fp)
    {
        fprintf(stderr, "ERROR: Unable to open file '%s'\n", argv[1]);
        return -1;
    }

    std::string str;
    filedump(str, fp);

    std::fputs(str.c_str(), stdout);

    std::fclose(fp);
}
