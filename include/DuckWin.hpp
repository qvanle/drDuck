#ifndef WINDOW
#define WINDOW

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_events.h>

#include <Display.hpp>

class MyWindow
{
private:
    int status;
    int WIDTH;
    int HEIGHT;

    SDL_Window* window;
    SDL_Renderer* renderer;
    std::stack<Display*> ScreenFlow;

    void shutdown();

public:
    MyWindow();
    void init();
    void action();
    void render();
    bool isOpen();
    bool isClose();

    void push(const char* name);
    void pop();
    bool empty();
    Display *& top();

    ~MyWindow();
};

#endif
