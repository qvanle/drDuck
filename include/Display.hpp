#ifndef DISPLAY
#define DISPLAY

#include <SDL2/SDL.h>
#include <SDL_surface.h>

class Display
{
private:
    SDL_Texture* background;
    SDL_Renderer *& renderer;
public:
    void init(const char* dir, const char* name);
    void setRenderer(SDL_Renderer *& ren);
};

#endif
