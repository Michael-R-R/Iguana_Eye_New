#include "IEHash.h"
#include <cstring>

// https://en.wikipedia.org/wiki/Jenkins_hash_function
unsigned long long IEHash::Compute(const char* str)
{
    unsigned long long value = 0;

    for(int i = 0; i < strlen(str); i++)
    {
        value += str[i];
        value += value << 10;
        value ^= value >> 6;
    }

    value += value << 3;
    value ^= value >> 11;
    value += value << 15;

    return value;
}
