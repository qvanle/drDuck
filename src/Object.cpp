#include <Object.hpp>

/**
 * @brief constructor of Object
*/

Object::Object()
{
    setCoor(0, 0, 0, 0);
    hide();
    tes.clear();
    ren = nullptr;
    top = 0;
}

/**
 * @brief load textures from an image which infomatition is in json file
 * @param mem json file
*/
void Object::initTextures(const json& mem)
{
    if(mem.contains("textures"))
    {
        setTextures(mem);
    }
}
/**
 * @brief load coordinate from json file
 * @param mem json file
*/
void Object::initRect(const json& mem)
{
    if(mem.contains("rect"))
    {
        if(mem["rect"].contains("x"))
            setX(mem["rect"]["x"]);
        if(mem["rect"].contains("y"))
            setY(mem["rect"]["y"]);
        if(mem["rect"].contains("w"))
            setW(mem["rect"]["w"]);
        if(mem["rect"].contains("h"))
            setH(mem["rect"]["h"]);
    }
}
/**
 * @brief load visible from json file
 * @param mem json file
*/
void Object::initVisible(const json& mem)
{
    if(mem.contains("visible"))
    {
        bool x = mem["visible"];
        if(x == true) show();
        else hide();
    }
}
/**
 * @brief init this object by json file
 * @param mem json file
 * @param r renderer
*/
void Object::init(const json& mem, SDL_Renderer *& r)
{
    ren = r;

    Sketch::init(mem);

    initTextures(mem);
    initRect(mem);
    initVisible(mem);
}
/**
 * @brief set coordinate of this object
 * @param x x coordinate
 * @param y y coordinate
 * @param w width
 * @param h height
*/
void Object::setCoor(int x, int y, int w, int h)
{
    coor.x = x;
    coor.y = y;
    coor.w = w;
    coor.h = h;
}
/**
 * @brief set coordinate of this object
 * @param key SDL_Rect
*/
void Object::setCoor(SDL_Rect key)
{
    coor.x = key.x;
    coor.y = key.y;
    coor.w = key.w;
    coor.h = key.h;
}
/**
 * @brief set x coordinate of this object
 * @param x x coordinate
*/
void Object::setX(int x)
{
    coor.x = x;
}
/**
 * @brief set y coordinate of this object
 * @param y y coordinate
*/
void Object::setY(int y)
{
    coor.y = y;
}
/**
 * @brief set width of this object
 * @param w width
*/
void Object::setW(int w)
{
    coor.w = w;
}
/**
 * @brief set height of this object
 * @param h height
*/
void Object::setH(int h)
{
    coor.h = h;
}
/**
 * @brief return coordinate of this object
*/
const SDL_Rect &Object::getCoor()
{
    return coor;
}
/**
 * @brief show this object
*/
void Object::show()
{
    visable = true;
}
/**
 * @brief hide this object
*/
void Object::hide()
{
    visable = false;
}
/**
 * @brief load textures from json file
*/
void Object::setTextures(const json &mem)
{
    clearTextures();

    tes.resize(mem["textures"].size());

    char* FolderName = new char [256];
    strcpy(FolderName, mem["name"].get<std::string>().c_str());

    for(int i = 0 ; i < size(); i++)
    {
        const char* fullname = combineName(
            mem["textures"][i]["name"].get<std::string>().c_str(),
            mem["textures"][i]["type"].get<std::string>().c_str()
        );
        const char* name = combineLink( 
            FolderName,
            fullname
        );
        const char* link = combineLink(
            GLOBAL::GraphicsFolder, 
            name
        ); 
        
        SDL_Surface* surf;

        std::string type = mem["textures"][i]["type"].get<std::string>();
        if(type == "bmp")
            surf = SDL_LoadBMP(link);
        else if(type == "png" || type == "jpg")
            surf = IMG_Load(link);

        tes[i] = SDL_CreateTextureFromSurface(ren, surf);

        delete [] link;
        delete [] name;
        delete []fullname;
        SDL_FreeSurface(surf);
    }
    delete [] FolderName;
}


Object::~Object()
{
    clearTextures();
    setCoor(0, 0, 0, 0);
    hide();
    ren = nullptr;
    top = 0;
}
/**
 * @brief return number of textures
*/
int Object::size()
{
    return tes.size();
}
/**
 * @brief clear all textures
*/
void Object::clearTextures()
{
    if(!tes.empty())
    {
        for(int i = 0; i < size(); i++)
        {
            if(tes[i] != nullptr) 
                SDL_DestroyTexture(tes[i]);
        }
        tes.clear();
    }
}

/**
 * @brief choose top texture
*/
void Object::pickTexure(int k)
{
    if(k >= size()) return ;
    top = k;
}
/**
 * @brief render this object
*/
void Object::render(bool update)
{
    if(!isVisible()) return ; 
    SDL_RenderCopy(ren, tes[top], nullptr, &coor);
    if(update == true)
        SDL_RenderPresent(ren);
    return ;
}
/**
 * @brief return true if this object is visible
*/
bool Object::isVisible()
{
    return visable;
}

/**
 * @brief return true if a point lies inside this object
*/
bool Object::isLiesInside(int x, int y)
{
    if(x < coor.x || coor.x + coor.w <= x)
        return false;
    if(y < coor.y || coor.y + coor.h <= y)
        return false;
    return true;
}
/**
 * @brief return true if a rectangle inside this object
*/
bool Object::isLiesInside(int x, int y, int w, int h)
{
    if(x < coor.x || coor.x + coor.w <= x + w)
        return false;
    if(y < coor.y || coor.y + coor.h <= y + h)
        return false;
    return true;
}
/**
 * @brief return true if a rectangle inside this object
*/
bool Object::isLiesInside(SDL_Rect rect)
{
    return isLiesInside(rect.x, rect.y, rect.w, rect.h);
}
/**
 * @brief add k to x coordinate
*/
void Object::addX(int k)
{
    coor.x += k;
}
/**
 * @brief add k to y coordinate
*/
void Object::addY(int k)
{
    coor.y += k;
}
/**
 * @brief add k to width
*/
void Object::addW(int k)
{
    coor.w += k;
}
/**
 * @brief add k to height
*/
void Object::addH(int k)
{
    coor.h += k;
}

/**
 * @brief move this object to (x, y) in time seconds
*/
void Object::moveTo(int x, int y, double time)
{
    int dx = x - getCoor().x;
    int dy = y - getCoor().y;

    if(diff(time, 0))
    {
        coor.x = x;
        coor.y = y;
        return ;
    }

    double velo;
    if(abs(dx) < abs(dy))
        velo = dy / time;
    else velo = dx / time;

    int loop = std::min(80.0, abs(velo * time));

    time = time / loop;


    for(int i = 1; i <= loop; i++)
    {
        Uint32 startTime = SDL_GetTicks();

        addX(-dx * (i - 1) / loop);
        addX(dx * i / loop);
        addY(-dy * (i - 1) / loop);
        addY(dy * i / loop);
        render(true); 
        Uint32 deltaTime = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();

        if(deltaTime <= time * 1000)
            SDL_Delay(time * 1000 - deltaTime);
    }
    setX(x);
    setY(y);
    render(true);
}
