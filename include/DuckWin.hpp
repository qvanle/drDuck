#ifndef WINDOW
#define WINDOW

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <Display.hpp>
#include <Data_Structures.hpp>
#include <SYSTEM.hpp>


class MyWindow
{
private:
    int status;
    int WIDTH;
    int HEIGHT;
    int FocusOn;
    int fps;

    Data_Structures* DT;

    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<Display*> screen;
    void shutdown();
    void deleteScreen();

    SDL_Event event;
    std::mutex UImutex;

public:
    MyWindow();
    void loadScreen(Display *& screen, const json& mem);
    void init();
    void action();
    void process();
    void render();
    bool isOpen();
    bool isClose();
    bool isHanging();

    void changeScreens(const char* const &name);
    Display *& top();

    void mouseMove(int x, int y);
    void mousePress(int x, int y);
    void run();

    ~MyWindow();
};

#endif
