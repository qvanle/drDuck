#ifndef SYSTEM
#define SYSTEM

#include <iostream>
#include <fstream>
#include <cstring>
#include <nlohmann/json_fwd.hpp>
#include <stack>
#include <string>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

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
void readJson(const char* const& link, json &mem);
void readjson(const char* const& dir, const char* const& name, json &mem);

#endif

