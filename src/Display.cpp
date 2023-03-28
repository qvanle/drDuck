#include <Display.hpp>
#include <cstring>

Display::Display()
{
    background = nullptr;
    renderer = nullptr;

    coor.x = 0;
    coor.y = 0;
    coor.w = 960;
    coor.h = 540;
}

void Display::init(const char *dir, const char *name)
{

    char* link = combineLink(dir, name);
    std::ifstream fin(link);
    
    json mem; 

    fin >> mem;

    fin.close();
    delete [] link;
    if(mem.contains("background"))
    {
        loadBackground(mem["background"]);
    }
}

void Display::loadBackground(const json& mem)
{
    if(!mem.contains("name") || !mem.contains("type"))
    {
        return ;
    }

    char* name = combineName(
        mem["name"].get<std::string>().c_str(),
        mem["type"].get<std::string>().c_str()    
    );

    char* link = combineLink(
        GLOBAL::BackgroundFolder, 
        name
    );

    delete [] name;
    SDL_Surface* surf = SDL_LoadBMP(link);

    background = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);
    delete [] link;
    
    if(!mem.contains("rect"))
    {
        return ;
    }

    coor.x = mem["rect"]["x"];
    coor.y = mem["rect"]["y"];
    coor.w = mem["rect"]["w"];
    coor.h = mem["rect"]["h"];
}

void Display::setRenderer(SDL_Renderer* const&  ren)
{
    renderer = ren;
}

void Display::render() 
{
    SDL_RenderCopy(renderer, background, nullptr, &coor);
}
Display::~Display()
{
    SDL_DestroyTexture(background);
    renderer = nullptr;
    coor.x = 0;
    coor.y = 0;
    coor.w = 0;
    coor.h = 0;
}

