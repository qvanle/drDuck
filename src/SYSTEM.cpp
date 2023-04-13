#include <SYSTEM.hpp>

const char* GLOBAL::GraphicsFolder = "asset/graphics/";

const char* GLOBAL::BackgroundFolder = "asset/graphics/";
const char* GLOBAL::ButtonFolder = "asset/graphics/";
const char* GLOBAL::AttributeFolder = "asset/attribute/";
const char* GLOBAL::AtrbScreens = "asset/attribute/screens/";
const char* GLOBAL::AtrbButtons = "asset/attribute/buttons/";
const char* GLOBAL::FontsFolder = "asset/fonts";


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
