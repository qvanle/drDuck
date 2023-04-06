#include "Display.hpp"
#include "SDL_image.h"
#include <DuckWin.hpp>

MyWindow::MyWindow()
{
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
    window = nullptr;
    renderer = nullptr;
    FocusOn = 0;
    screen = new Display*[1];
}


void MyWindow::init()
{
    status = 1;
    WIDTH = 960;
    HEIGHT = 540;

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow(
        "Dr Duck",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED 
    );

    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
}

void MyWindow::render()
{
    SDL_RenderClear(renderer);
    
    if(top() != nullptr) top()->render();

    SDL_RenderPresent(renderer);
}

void MyWindow::changeFocus(int x, int y)
{
    top()->changeFocus(x, y);
    top()->mouseMove(x, y);
}

void MyWindow::action()
{

    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT)
        {
            status = 0;
            shutdown();
        }else if(event.type == SDL_MOUSEMOTION)
        {
            changeFocus(event.motion.x, event.motion.y);
        }else if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            char* msg = nullptr;
            top()->mousePressedButton(event.motion.x, event.motion.y, msg);
            
            if(msg == nullptr) continue;

            changeScreen(msg);
            delete [] msg;
        }
    }
}

void MyWindow::shutdown()
{
    if(window != nullptr)
    {
        SDL_DestroyWindow(window);
        window = nullptr;
        SDL_Quit();
    }
    if(renderer != nullptr)
    {

        SDL_DestroyRenderer(renderer);
        renderer= nullptr;
    }
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
    if(screen != nullptr) 
    {
        delete screen;
        screen = nullptr;
    }

    IMG_Quit();
} 

bool MyWindow::isOpen()
{
    return status == 1;
}

bool MyWindow::isClose()
{
    return status == 0;
}

void MyWindow::changeScreen(const char *const& name)
{
    if(top() != nullptr)
    {
        delete top();
        top() = nullptr;
    }
    top() = new Display;
    top()->setRenderer(renderer);
    top()->init(GLOBAL::AtrbScreens, name);
}

Display *& MyWindow::top()
{
    return screen[FocusOn];
}

MyWindow::~MyWindow()
{
    shutdown();
}
