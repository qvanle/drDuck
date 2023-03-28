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
public:
    Display();
    void init(const char* dir, const char* name);
    void loadBackground(json mem);
    void setRenderer(SDL_Renderer* const&  ren);
    void render();
    ~Display();
};

#endif
