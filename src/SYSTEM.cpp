#include <SYSTEM.hpp>

const char* GLOBAL::BackgroundFolder = "asset/background/";
const char* GLOBAL::ButtonFolder = "asset/buttons/";
const char* GLOBAL::AttributeFolder = "asset/attribute/";
const char* GLOBAL::AtrbScreens = "asset/attribute/screens/";
const char* GLOBAL::AtrbButtons = "asset/attribute/buttons/";


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
