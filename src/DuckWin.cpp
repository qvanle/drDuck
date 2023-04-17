#include "SDL_ttf.h"
#include "Sketch.hpp"
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
    wait = false;
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
    TTF_Init();

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = WIDTH;
    rect.h = HEIGHT;

    SDL_RenderSetViewport(renderer, &rect);
}

void MyWindow::render()
{
    TTF_Font* font = TTF_OpenFont("asset/fonts/Atomed.ttf", 20);
    Sketch* a;
    a = new Sketch;
    a->setFont(font);
    a->setColor(125, 45, 125, 255);
    a->setX(10);
    a->setY(10);
    a->setRender(renderer);
    a->setText("hehehehehehe");
    wait = true;
    while(isOpen())
    {
        SDL_RenderClear(renderer);

        for(int i = 0; i < ScreenNum; i++)
            screen[i]->render();
        a->render();

        SDL_RenderPresent(renderer);
        while(isOpen() && (wait || isHanging()));
    }
}

void MyWindow::mouseMove(int x, int y)
{
    for(int i = ScreenNum - 1; i >= 0; i--)
    {
        if(screen[i]->isVisible() && screen[i]->isLiesInside(x, y))
        {
            FocusOn = i;
            screen[i]->changeFocus(x, y);
            screen[i]->mouseMove(x, y);
        }else if (!screen[i]->isVisible() && screen[i]->isLiesInside(x, y))
        {
            if(screen[i]->getAppear() == 0) continue;
            else if(screen[i]->getAppear() == 1) screen[i]->appearFromBot(0.4);
            else if(screen[i]->getAppear() == 2) screen[i]->appearFromRight(0.4);
            FocusOn = i;
            screen[i]->changeFocus(x, y);
            screen[i]->mouseMove(x, y);
        }else if(screen[i]->isVisible() && !screen[i]->isLiesInside(x, y))
        {
            if(screen[i]->getAppear() == 0) continue;
            else if(screen[i]->getAppear() == 1) screen[i]->disappearToBot(0.4);
            else if(screen[i]->getAppear() == 2) screen[i]->disappearToRight(0.4);
        }
    }
}

void MyWindow::mousePress(int x, int y)
{

    Button* but = top()->mousePressedButton(x, y);

    if(but == nullptr) return ;

    if(but->getAction() == "change screen")
    {
        changeScreens(but->getNextScreen());
        mouseMove(x, y);
    }
}

void MyWindow::action()
{
    while(isOpen())
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
                mouseMove(event.motion.x, event.motion.y);
            }else if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                mousePress(event.motion.x, event.motion.y);
            }
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
    TTF_Quit();
} 

bool MyWindow::isOpen()
{
    return status == 1;
}

bool MyWindow::isHanging()
{
    return status == 2;
}

bool MyWindow::isClose()
{
    return status == 0;
}

void MyWindow::changeScreens(const char *const& name)
{
    wait = true;
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
    wait = false;
}

Display *& MyWindow::top()
{
    return screen[FocusOn];
}
MyWindow::~MyWindow()
{
    shutdown();
}

void MyWindow::run()
{
    std::thread draw(&MyWindow::render, this);
    std::thread interact(&MyWindow::action, this);

    draw.join();
    interact.join();
}
