#include <Display.hpp>


Display::Display()
{
    background = nullptr;
    renderer = nullptr;
}

void Display::setRenderer(SDL_Renderer* const&  ren)
{
    renderer = ren;
}

Display::~Display()
{
    SDL_DestroyTexture(background);
    renderer = nullptr;
}
