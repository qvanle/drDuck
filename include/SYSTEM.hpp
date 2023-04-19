#ifndef SYSTEM
#define SYSTEM

#include <iostream>
#include <fstream>
#include <cstring>
#include <stack>
#include <string>
#include <thread>
#include <mutex>
#include <algorithm>
#include <random>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace GLOBAL
{
    extern const char* GraphicsFolder;
    extern const char* BackgroundFolder;
    extern const char* ButtonFolder;
    extern const char* AttributeFolder;
    extern const char* AtrbScreens;
    extern const char* AtrbButtons;
    extern const char* FontsFolder;
}

namespace RANDOM 
{
    extern std::mt19937 rng;
    void init();
    int getInt(int l, int r);
    double getDouble(double l, double r);
}

char * combineLink(const char* dir, const char* name);
char * combineName(const char* name, const char* type);
void readJson(const char* const& link, json &mem);
void readjson(const char* const& dir, const char* const& name, json &mem);

bool diff(double a, double b);
#endif

