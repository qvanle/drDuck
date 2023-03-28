#include <SYSTEM.hpp>

const char* GLOBAL::BackgroundFolder = "asset/background/";
const char* GLOBAL::ButtonFolder = "asset/buttons/";
const char* GLOBAL::AttributeFolder = "asset/attribute/";

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
