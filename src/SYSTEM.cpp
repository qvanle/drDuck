#include <SYSTEM.hpp>

/**
 * @brief path to the folder that store all graphics 
*/
const char* GLOBAL::GraphicsFolder = "asset/graphics/";

/**
 * @brief path to the folder that store all background asset 
*/
const char* GLOBAL::BackgroundFolder = "asset/graphics/";
/**
 * @brief path to the folder that store all button asset 
*/
const char* GLOBAL::ButtonFolder = "asset/graphics/";

/**
 * @brief path to the folder that store all custom attribute of graphics, sound, etc
*/
const char* GLOBAL::AttributeFolder = "asset/attribute/";
/**
 * @brief path to the folder that store all custom attribute of screens
*/
const char* GLOBAL::AtrbScreens = "asset/attribute/screens/";
/**
 * @brief path to the folder that store all custom attribute of buttons
*/
const char* GLOBAL::AtrbButtons = "asset/attribute/buttons/";
/**
 * @brief path to the folder that store all custom attribute of fonts
*/
const char* GLOBAL::FontsFolder = "asset/fonts";
/**
 * @brief path to the folder that store all custom attribute of input box
*/
const std::string GLOBAL::AtrbInputBox = "asset/attribute/InputBox/";
/**
 * @brief path to the folder that store all custom attribute of data structures
*/
const std::string GLOBAL::AtrbDT = "asset/attribute/DataStructures/";
/**
 * @brief path to the folder that store all custom attribute of script
*/
const std::string GLOBAL::AtrbScript = "asset/attribute/script/";
/**
 * @brief time to wait for the next action
 * 
 * for step to step feature
*/
const int GLOBAL::WAITING = 800;
/**
 * @brief path to the folder that store all custom attribute of sound
*/
const std::string GLOBAL::SoundFolder = "asset/sound/";


/**
 * @brief random number generator
*/
std::mt19937 RANDOM::rng;
/**
 * @brief initialize random number generator
 * 
 * call this before using random 
*/
void RANDOM::init()
{
    rng = std::mt19937(std::chrono::steady_clock::now().time_since_epoch().count());
}
/**
 * @brief get random integer in range [l, r]
 * @param l interger, left bound
 * @param r integer, right bound
*/
int RANDOM::getInt(int l, int r)
{
    return std::uniform_int_distribution<int> (l, r)(rng);
}
/**
 * @brief get random double in range [l, r]
 * @param l double, left bound
 * @param r double, right bound
*/
double RANDOM::getDouble(double l, double r)
{
    return std::uniform_real_distribution<double> (l, r)(rng);
}
/**
 * @brief combine a name and a extension to a full file name 
 * 
 * exam 1: combine "asd" and "bcs" in to "asd.bcs"
 * 
 * exam 2: combine "asd." and "bsc" into "asd.bcs"
 * 
 * exam 3: combine "asd" and ".bcs" into "asd.bcs"
 * 
 * exam 4: combine "asd." and ".bcs" into "asd.bcs"
 * 
 * @param name cstring, the name
 * @param type cstring, the extension
*/
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
/**
 * @brief combine a directory and a file to a full file name
 * 
 * exam 1: combine "asd" and "bcs" in to "asd/bcs"
 * 
 * exam 2: combine "asd/" and "bsc" into "asd/bsc"
 * 
 * exam 3: combine "asd" and "/bcs" into "asd/bcs"
 * 
 * exam 4: combine "asd/" and "/bcs" into "asd/bcs"
 * 
 * @param dir cstring, the directory
 * @param name cstring, the file name
*/
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
/**
 * @brief opean a json file which path is string s and store it in mem
 * 
 * @param s string, the path to the json file
 * @param mem json, the json object to store the data
*/
void readJson(std::string s, json &mem)
{
    readJson(s.c_str(), mem);
}

/**
 * @brief opean a json file which path is string s and store it in mem
 * 
 * @param link cstring, the path to the json file
 * @param mem json, the json object to store the data
*/
void readJson(const char * const& link, json &mem)
{
    std::ifstream fin(link);
    
    fin >> mem;

    fin.close();
    return ;
}
/**
 * @brief opean a json file which path is string dir and file name is name. Store it in mem
 * 
 * @param dir cstring, the path to the directory
 * @param name cstring, the name of the file
 * @param mem json, the json object to store the data
*/

void readjson(const char * const& dir, const char * const& name, json &mem)
{
    char* link = combineLink(dir, name);

    readJson(link, mem);

    delete [] link;
}
/**
 * @brief determine if a double is equal to another double
 * 
 * @param a double, the first double
 * @param b double, the second double
 * @return true if a == b (error is less than 1e-6)
*/
bool diff(double a, double b)
{
    return fabs(a - b) < 1e-6;
}
/**
 * @brief get the first interger in a string 
 * 
 * if the string is "asd123", return 123
 * 
 * if the string is "123asd", return 123
 * 
 * if the string is "asd123asd", return 123
 * 
 * if the string is "asd", return 0
 * 
 * if the string is "1a2" return 1
 * 
 * @param s string, the string to get the first interger
*/
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
/** 
 * @brief get the first 3 number in a string 
 * @param s string, the string to get the first 3 number
 * @param r int&, the first number
 * @param g int&, the second number
 * @param b int&, the third number
*/
void getColor(std::string s, int &r, int &g, int &b)
{
    int i = 0;
    r = 0;
    g = 0;
    b = 0;

    while(i < (int)s.size() && !isdigit(s[i]))
        i++;
    while(i < (int) s.size() && isdigit(s[i]))
        r = r * 10 + s[i++] - '0';
    
    while(i < (int)s.size() && !isdigit(s[i]))
        i++;
    while(i < (int) s.size() && isdigit(s[i]))
        g = g * 10 + s[i++] - '0';

    while(i < (int)s.size() && !isdigit(s[i]))
        i++;
    while(i < (int) s.size() && isdigit(s[i]))
        b = b * 10 + s[i++] - '0';
}
