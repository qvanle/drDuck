#ifndef SYSTEM
#define SYSTEM

#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>

namespace GLOBAL
{
    extern const char* BackgroundFolder;
    extern const char* ButtonFolder;
    extern const char* AttributeFolder;
}

char * combineLink(const char *dir, const char *name);

#endif
