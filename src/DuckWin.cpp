#include "Display.hpp"
#include "SDL_image.h"
#include "SDL_mutex.h"
#include <DuckWin.hpp>

MyWindow::MyWindow()
{
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
    window = nullptr;
    renderer = nullptr;
    FocusOn = 0;
    screen = nullptr; 
    ScreenNum = 0;
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
    
    for(int i = 0; i < ScreenNum; i++)
        screen[i]->render();

    SDL_RenderPresent(renderer);
}

void MyWindow::changeFocus(int x, int y)
{
    for(int i = 0; i < ScreenNum; i++)
    {
        screen[i]->changeFocus(x, y);
        screen[i]->mouseMove(x, y);
    }
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

            changeScreens(msg);
            changeFocus(event.motion.x, event.motion.y);

            delete [] msg;
        }
    }
}

void MyWindow::deleteScreen()
{
    if(screen == nullptr) return ;
    delete [] screen;
    screen = nullptr;
}

void MyWindow::shutdown()
{
    deleteScreen();
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

void MyWindow::changeScreens(const char *const& name)
{
    deleteScreen();

    json mem; 

    readjson(GLOBAL::AtrbScreens, name, mem);

    ScreenNum = mem.size();

    screen = new Display*[ScreenNum];

    for(int i = 0; i < ScreenNum; i++)
    {
        FocusOn = i;
        top() = new Display;
        top()->setRenderer(renderer);
        top()->init(mem[i]);
    }
    FocusOn = 0;
}

Display *& MyWindow::top()
{
    return screen[FocusOn];
}
MyWindow::~MyWindow()
{
    shutdown();
}
