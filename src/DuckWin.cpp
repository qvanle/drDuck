#include <DuckWin.hpp>

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
        0
    );
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

    SDL_Quit();
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
} 

bool MyWindow::isOpen()
{
    return status == 1;
}

bool MyWindow::isClose()
{
    return status == 0;
}
