#include "SYSTEM.hpp"
#include <DuckWin.hpp>

MyWindow::MyWindow()
{
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
    window = nullptr;
    renderer = nullptr;
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
}

void MyWindow::render()
{
    SDL_RenderClear(renderer);
    
    if(!empty()) ScreenFlow.top()->render();

    SDL_RenderPresent(renderer);
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
        }
    }
}

void MyWindow::shutdown()
{
    if(window == nullptr) return ;
    SDL_DestroyWindow(window);
    window = nullptr;
    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    SDL_Quit();
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;

    while(!empty())
        pop();
} 

bool MyWindow::isOpen()
{
    return status == 1;
}

bool MyWindow::isClose()
{
    return status == 0;
}

void MyWindow::push(const char *name)
{
    ScreenFlow.push(nullptr);
    top() = new Display;
    top()->setRenderer(renderer);
    top()->init(GLOBAL::AtrbScreens, name);

}

void MyWindow::pop()
{
    delete ScreenFlow.top();
    ScreenFlow.pop();
}

Display *& MyWindow::top()
{
    return ScreenFlow.top();
}

bool MyWindow::empty()
{
    return ScreenFlow.empty();
}

MyWindow::~MyWindow()
{
    shutdown();
}
