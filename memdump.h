// memdump.h --- C++ memory dumper

#pragma once

#include <ctype.h>
#include <assert.h>

#define MEMDUMP_BYTE_TO_HEX(buf, byte, hex) do { \
    assert((sizeof(buf) / sizeof(buf[0])) >= 3); \
    (buf)[0] = (hex)[(byte) >> 4]; \
    (buf)[1] = (hex)[(byte) & 0xF]; \
    (buf)[2] = 0; \
} while (0)

#define MEMDUMP_DWORD_TO_HEX(buf, dword, hex) do { \
    assert((sizeof(buf) / sizeof(buf[0])) >= 9); \
    (buf)[0] = (hex)[((dword) >> 28) & 0xF]; \
    (buf)[1] = (hex)[((dword) >> 24) & 0xF]; \
    (buf)[2] = (hex)[((dword) >> 20) & 0xF]; \
    (buf)[3] = (hex)[((dword) >> 16) & 0xF]; \
    (buf)[4] = (hex)[((dword) >> 12) & 0xF]; \
    (buf)[5] = (hex)[((dword) >> 8) & 0xF]; \
    (buf)[6] = (hex)[((dword) >> 4) & 0xF]; \
    (buf)[7] = (hex)[((dword) >> 0) & 0xF]; \
    (buf)[8] = 0; \
} while (0)

struct MEMDUMP_SETTINGS
{
    size_t addr_base;
    size_t column;
    bool has_addr;
    bool has_header;
    const char *hex;

    MEMDUMP_SETTINGS()
    {
        addr_base = 0;
        column = 16;
        has_addr = true;
        has_header = true;
        hex = "0123456789ABCDEF";
    }
};

template <typename T_STRING>
void memdump(T_STRING& str, const void *ptr, size_t size, const MEMDUMP_SETTINGS& settings)
{
    size_t addr_base = settings.addr_base, column = settings.column;
    bool has_addr = settings.has_addr, has_header = settings.has_header;
    const char *hex = settings.hex;
    const unsigned char *pb = reinterpret_cast<const unsigned char *>(ptr);

    assert(1 < column);
    assert(column <= 0x100);

    size_t i, j, count;

    // header
    if (has_header)
    {
        // addr
        if (has_addr)
            str += "+ADDRESS  ";

        // column offsets
        for (i = 0; i < column; ++i)
        {
            if (i < 16)
            {
                str += '+';
                str += hex[i & 0xF];
            }
            else
            {
                str += hex[i >> 4];
                str += hex[i & 0xF];
            }
            str += ' ';
        }
        str += ' ';

        // text offsets
        for (i = 0; i < column; ++i)
        {
            str += hex[i & 0xF];
        }

        // new line
        str += '\n';
    }

    // body
    char buf[9];
    for (i = 0; i < size; i += column)
    {
        // addr
        if (has_addr)
        {
            MEMDUMP_DWORD_TO_HEX(buf, addr_base + i, hex);
            str += buf;
            str += "  ";
        }

        count = (i + column < size) ? column : (size - i);

        // hex
        for (j = 0; j < count; j++)
        {
            MEMDUMP_BYTE_TO_HEX(buf, pb[i + j], hex);
            buf[2] = ' ';
            buf[3] = 0;
            str += buf;
        }

        for (j = 0; j < 3 * (column - count) + 1; ++j)
            str += ' ';

        // text
        for (j = 0; j < count; j++)
        {
            if (isprint(pb[i + j]))
                str += pb[i + j];
            else
                str += '.';
        }

        // new line
        str += '\n';
    }
}

template <typename T_STRING>
void memdump(T_STRING& str, const void *ptr, size_t size)
{
    MEMDUMP_SETTINGS settings;
    memdump(str, ptr, size, settings);
}

#undef MEMDUMP_BYTE_TO_HEX
#undef MEMDUMP_DWORD_TO_HEX
