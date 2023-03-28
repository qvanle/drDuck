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
    extern const char* AtrbScreens;
    extern const char* AtrbButtons;
}

char * combineLink(const char* dir, const char* name);
char * combineName(const char* name, const char* type);
#endif
