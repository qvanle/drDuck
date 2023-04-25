#include <SYSTEM.hpp>
#include <random>

const char* GLOBAL::GraphicsFolder = "asset/graphics/";

const char* GLOBAL::BackgroundFolder = "asset/graphics/";
const char* GLOBAL::ButtonFolder = "asset/graphics/";
const char* GLOBAL::AttributeFolder = "asset/attribute/";
const char* GLOBAL::AtrbScreens = "asset/attribute/screens/";
const char* GLOBAL::AtrbButtons = "asset/attribute/buttons/";
const char* GLOBAL::FontsFolder = "asset/fonts";
const std::string GLOBAL::AtrbInputBox = "asset/attribute/InputBox/";
const std::string GLOBAL::AtrbDT = "asset/attribute/DataStructures/";
const std::string GLOBAL::AtrbScript = "asset/attribute/script/";
const int GLOBAL::WAITING = 800;

std::mt19937 RANDOM::rng;

void RANDOM::init()
{
    rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
}

int RANDOM::getInt(int l, int r)
{
    return std::uniform_int_distribution<int> (l, r)(rng);
}

double RANDOM::getDouble(double l, double r)
{
    return std::uniform_real_distribution<double> (l, r)(rng);
}

char * combineName(const char *name, const char *type)
{
    int n = strlen(name);
    int m = strlen(type);
    char* link = new char[n + m + 5];

    strcpy(link, name);

    if(name[n - 1] == '.' && type[0] == '.')
        link[n - 1] = '\0';
    else if(name[n - 1] != '.' && type[0] != '.')
    {
        strcat(link, ".");
    }

    strcat(link, type);

    return link;
}

char * combineLink(const char *dir, const char *name)
{

    int n = strlen(dir);
    int m = strlen(name);
    char* link = new char[n + m + 5];

    strcpy(link, dir);

    if(dir[n - 1] == '/' && name[0] == '/')
        link[n - 1] = '\0';
    else if(dir[n - 1] != '/' && name[0] != '/')
    {
        strcat(link, "/");
    }

    strcat(link, name);

    return link;
}

void readJson(std::string s, json &mem)
{
    readJson(s.c_str(), mem);
}


void readJson(const char * const& link, json &mem)
{
    std::ifstream fin(link);
    
    fin >> mem;

    fin.close();
    return ;
}

void readjson(const char * const& dir, const char * const& name, json &mem)
{
    char* link = combineLink(dir, name);

    readJson(link, mem);

    delete [] link;
}

bool diff(double a, double b)
{
    return fabs(a - b) < 1e-6;
}

int getFirstInt(std::string s)
{
    int res = 0;
    int i = 0;

    while(i < (int) s.size() && !isdigit(s[i]))
        i++;
    while(i < (int) s.size() && isdigit(s[i]))
    {
        res = res * 10 + s[i] - '0';
        i++;
    }
    return res;
}
