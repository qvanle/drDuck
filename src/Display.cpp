#include "SDL_render.h"
#include <Display.hpp>
#include <cstring>

Display::Display()
{
    background = nullptr;
    renderer = nullptr;
}

void Display::init(const char *dir, const char *name)
{
    char* link = combineLink(dir, name);
    std::ifstream fin(link);
    
    json mem; 

    fin >> mem;

    fin.close();
    delete [] link;

    loadBackground(mem["background"]);
}

void Display::loadBackground(json mem)
{
    char* name = new char[512];
    strcpy(name, mem["name"].get<std::string>().c_str());
    strcat(name, ".");
    strcat(name, mem["type"].get<std::string>().c_str());

    char* link = combineLink(GLOBAL::BackgroundFolder, name);

    delete [] name;
    SDL_Surface* surf = SDL_LoadBMP(link);

    background = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);
    delete [] link;

    std::cerr << SDL_GetError() << std::endl;
}

void Display::setRenderer(SDL_Renderer* const&  ren)
{
    renderer = ren;
}

void Display::render() 
{
    SDL_Rect coor; 
    coor.x = 0;
    coor.y = 0;
    coor.h = 540;
    coor.w = 960;
    SDL_RenderCopy(renderer, background, nullptr, &coor);
}
Display::~Display()
{
    SDL_DestroyTexture(background);
    renderer = nullptr;
}
