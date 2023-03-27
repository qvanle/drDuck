#ifndef WINDOW
#define WINDOW

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_events.h>

class MyWindow
{
private:
    int status;
    int WIDTH;
    int HEIGHT;

    SDL_Window* window;
    SDL_Renderer* renderer;

    void shutdown();
    void Render();

public:
    MyWindow();
    void init();
    void action();
    bool isOpen();
    bool isClose();
    ~MyWindow();
};

#endif
