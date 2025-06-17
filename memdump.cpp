// memdump.cpp --- C++ memory dumper
#include <stdio.h>
#include <string.h>
#include <string>
#include "memdump.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::puts("Usage: memdump <file>");
        return 1;
    }

    printf("std::string version:\n");
    std::string str;
    memdump(str, argv[1], strlen(argv[1]));
    printf("%s\n", str.c_str());

#ifdef _WIN32
    printf("std::wstring version:\n");
    std::wstring wstr;
    memdump(wstr, argv[1], strlen(argv[1]));
    wprintf(L"%ls\n", wstr.c_str());
#endif

    return 0;
}
