#ifndef DISPLAY
#define DISPLAY

#include <SDL2/SDL.h>
#include <SDL_surface.h>
#include <SDL_render.h>

#include <nlohmann/json.hpp>

#include <SYSTEM.hpp>


using json = nlohmann::json;

class Display
{
private:
    SDL_Texture* background;
    SDL_Renderer * renderer;
    SDL_Rect coor;
public:
    Display();
    void init(const char* dir, const char* name);
    void loadBackground(const json& mem);
    void setRenderer(SDL_Renderer* const&  ren);
    void render();
    ~Display();
};

#endif
