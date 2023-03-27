#include <SYSTEM.hpp>

const char* GLOBAL::BackgroundFolder = "asset/background/";
const char* GLOBAL::ButtonFolder = "asset/buttons/";
const char* GLOBAL::AttributeFolder = "asset/attribute/";

char *& combineLink(const char *dir, const char *name)
{
    int n = strlen(dir);
    int m = strlen(name);
    static char* link = new char[n + m + 5];
    strcpy(link, dir);

    if(dir[m - 1] == '/' && name[0] == '/')
        link[m - 1] = '\0';
    else if(dir[m - 1] != '/' && name[0] != '/')
        strcat(link, "/");
    strcat(link, name);

    return link;
}
