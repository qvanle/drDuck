#include <DuckWin.hpp>

MyWindow::MyWindow()
{
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
    window = nullptr;
    renderer = nullptr;
    FocusOn = 0;
    screen.clear();
    DT = nullptr;
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
    fps = 60;

    SDL_RenderSetViewport(renderer, &rect);
}


void MyWindow::mouseMove(int x, int y)
{
    for(int i = 0; i < (int) screen.size(); i++)
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
        std::string type = but->getDataStructure();
        UImutex.lock();
        if(DT != nullptr) 
        {
            delete DT;
            DT = nullptr;
        }
        changeScreens(but->getNextScreen());
        if(type == "StaticArray.json")
        {
            DT = new Data_Structures;
            DT->setRender(renderer);
            json mem;
            readJson("asset/attribute/DataStructures/StaticArray.json", mem);
            DT->init(mem);
            readJson("saving/1.json", mem);
            DT->loadValue(mem);
        }
        UImutex.unlock();
    }
}


void MyWindow::deleteScreen()
{
    if(screen.empty()) return ;
    //for(int i = 0; i < (int) screen.size(); i++)
    //    screen[i]->~Display();
    screen.clear();
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
    deleteScreen();

    json mem; 

    readjson(GLOBAL::AtrbScreens, name, mem);

    screen.resize(mem.size());


    for(int i = 0; i < (int) screen.size(); i++)
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

void MyWindow::run()
{
    std::thread draw(&MyWindow::render, this);
    action();

    draw.join();
}

void MyWindow::render()
{

    double delayTime = 1000.0 / fps;
    while(isOpen())
    {
        if(UImutex.try_lock())
        {
            Uint32 startTime = SDL_GetTicks();
            SDL_RenderClear(renderer);

            for(int i = 0; i < (int) screen.size(); i++)
            {
                screen[i]->render();
                if(i == 0 && DT != nullptr) 
                {
                    DT->render();
                }
            }
            SDL_RenderPresent(renderer);
            UImutex.unlock();
            Uint32 DeltaTime = SDL_GetTicks() - startTime;
            if(DeltaTime < delayTime)
                SDL_Delay(delayTime - delayTime);
        }
    }
}

void MyWindow::process()
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
        mouseMove(event.motion.x, event.motion.y);
    }
}

void MyWindow::action()
{
    while(isOpen())
    {
        while(SDL_PollEvent(&event))
            process();
    }
}
