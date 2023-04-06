#ifndef WINDOW
#define WINDOW

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>

#include <Display.hpp>

class MyWindow
{
private:
    int status;
    int WIDTH;
    int HEIGHT;
    int FocusOn;

    SDL_Window* window;
    SDL_Renderer* renderer;
    Display ** screen;

    void shutdown();

public:
    MyWindow();
    void loadScreen(Display *& screen, const json& mem);
    void init();
    void action();
    void render();
    bool isOpen();
    bool isClose();

    void changeScreen(const char* const &name);
    Display *& top();

    void changeFocus(int x, int y);

    ~MyWindow();
};

#endif
