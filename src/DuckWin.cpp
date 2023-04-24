#include "Button.hpp"
#include "Data_Structures.hpp"
#include "SYSTEM.hpp"
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
    input = nullptr;
}


void MyWindow::init()
{
    status = 1;
    WIDTH = 960;
    HEIGHT = 540;
    RANDOM::init();

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
    if(input != nullptr) input->mouseMove(x, y);
}

bool MyWindow::isChangeScreen(Button *& but)
{
    if(but->getAction() == "change screen")
    {
        UImutex.lock();

        if(DT != nullptr && DT->isVisible())
        {
            DT->hide();
        }else {

            std::string type = but->getDataStructure();
            std::string screenName = but->getNextScreen();

            changeScreens(screenName.c_str());
            if(type == "StaticArray.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "DynamicArray.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "SinglyLinkedList.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(DT != nullptr) 
            {
                delete DT;
                DT = nullptr;
            }

            if(input != nullptr) 
            {
                delete input;
                input = nullptr;
            }
        }
        UImutex.unlock();
        return true;
    }
    return false;
}

bool MyWindow::isDToperator(Button *& but)
{
    if(but->getAction() == "new")
    {
        if(DT != nullptr && !DT->isFinish()) return false;
        UImutex.lock();
        if(input != nullptr)
        {
            delete input;
            input = nullptr;
        }
        json mem;
        readJson(GLOBAL::AtrbInputBox + "new.json", mem);
        input = new InputBox;
        input->setRender(renderer);
        input->init(mem);
        screen[1]->showButton(0);
        screen[1]->hideButton(1);
        UImutex.unlock();
        return true;
    }
    if(DT == nullptr || !DT->isVisible() || !DT->isFinish()) return false;
    if(but->getAction() == "delete")
    {
        UImutex.lock();
        if(input != nullptr) 
        {
            delete input;
            input = nullptr;
        }

        json mem;
        readJson(GLOBAL::AtrbInputBox + "delete.json", mem);
        input = new InputBox;
        input->setRender(renderer);
        input->init(mem);

        screen[1]->showButton(0);
        screen[1]->hideButton(1);
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "search")
    {
        UImutex.lock();
        if(input != nullptr) 
        {
            delete input;
            input = nullptr;
        }

        json mem;
        readJson(GLOBAL::AtrbInputBox + "search.json", mem);
        input = new InputBox;
        input->setRender(renderer);
        input->init(mem);

        screen[1]->showButton(0);
        screen[1]->hideButton(1);
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "update")
    {
        UImutex.lock();
        if(input != nullptr) 
        {
            delete input;
            input = nullptr;
        }

        json mem;
        readJson(GLOBAL::AtrbInputBox + "update.json", mem);
        input = new InputBox;
        input->setRender(renderer);
        input->init(mem);

        screen[1]->showButton(0);
        screen[1]->hideButton(1);
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "insert") 
    {
        UImutex.lock();
        if(input != nullptr)
        {
            delete input;
            input = nullptr;
        }
        json mem;
        readJson(GLOBAL::AtrbInputBox + "insert.json", mem);
        input = new InputBox;
        input->setRender(renderer);
        input->init(mem);

        screen[1]->showButton(0);
        screen[1]->hideButton(1);

        UImutex.unlock();
        return true;
    }
    return false;
}

bool MyWindow::isInputButton(Button *& but)
{
    if(input == nullptr) return false;
    if(but->getAction() == "hide input")
    {
        UImutex.lock();
        delete input;
        input = nullptr;
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "done new")
    {
        UImutex.lock();
        input->hide();
        DT->create(input->getText(0));
        DT->show();
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "random new")
    {
        UImutex.lock();
        int n = RANDOM::getInt(2, 12);
        std::string temp = "";
        for(int i = 0; i < n; i++)
        {
            temp = temp + std::to_string(RANDOM::getInt(0, 20));
            if(i + 1 != n) temp = temp + ", ";
        }
        input->setFocus(0);
        input->setInput(temp);
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "random position")
    {
        UImutex.lock();
        input->setFocus(0);
        input->setInput(std::to_string(RANDOM::getInt(0, DT->size())));
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "random value")
    {
        UImutex.lock();
        input->setFocus(1);
        input->setInput(std::to_string(RANDOM::getInt(0, 99)));
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "done insert")
    {
        UImutex.lock();
        input->hide();
        std::string s1 = input->getText(0);
        std::string s2 = input->getText(1);
        UImutex.unlock();
        std::thread insert(&Data_Structures::insert, DT, s1, s2, std::ref(UImutex));
        insert.detach();
        return true;
    }
    if(but->getAction() == "done delete") 
    {
        UImutex.lock();
        input->hide();
        std::string s1 = input->getText(0);
        UImutex.unlock();
        std::thread erase(&Data_Structures::erase, DT, s1, std::ref(UImutex));
        erase.detach();
        return true;
    }
    if(but->getAction() == "done update")
    {
        UImutex.lock();
        input->hide();
        std::string s1 = input->getText(0);
        std::string s2 = input->getText(1);
        UImutex.unlock();

        std::thread update(&Data_Structures::update, DT, s1, s2, std::ref(UImutex));
        update.detach();
        return true;
    }
    if(but->getAction() == "done search")
    {
        UImutex.lock();
        input->hide();
        std::string s2 = input->getText(1);
        UImutex.unlock();

        std::thread search(&Data_Structures::search, DT, s2, std::ref(UImutex));
        search.detach();
        return true;
    }
    return false;
}

bool MyWindow::isPlayButton(Button *& but)
{
    if(DT != nullptr && DT->isVisible() && but->getAction() == "pause") 
    {
        UImutex.lock();
        DT->setStep(0);
        but->hide();
        screen[1]->showButton(1);
        UImutex.unlock();
        return true;
    }
    if(DT != nullptr && DT->isVisible() && but->getAction() == "play")
    {
        UImutex.lock();
        DT->setStep(-1);
        but->hide();
        screen[1]->showButton(0);
        UImutex.unlock();
        return true;
    }
    if(DT != nullptr && DT->isVisible() && but->getAction() == "slow down")
    {
        UImutex.lock();
        DT->slowDown();
        UImutex.unlock();
        return true;
    }
    if(DT != nullptr && DT->isVisible() && but->getAction() == "speed up")
    {
        UImutex.lock();
        DT->speedUp();
        UImutex.unlock();
        return true;
    }
    if(DT != nullptr && DT->isVisible() && but->getAction() == "next")
    {
        UImutex.lock();
        DT->nextStep();
        UImutex.unlock();
        return true;
    }
    return false;
}

void MyWindow::mousePress(int x, int y)
{

    if(input != nullptr) input->mousePress(x, y);

    Button* but = nullptr;

    if(input != nullptr) but = input->getButtonPressedByMouse(x, y); 

    if(but == nullptr) 
        but = top()->mousePressedButton(x, y);

    if(but == nullptr) return ;
    if(isChangeScreen(but)) return ;
    if(isDToperator(but)) return;
    if(isInputButton(but)) return ;
    if(isPlayButton(but)) return ;
}


void MyWindow::deleteScreen()
{
    if(screen.empty()) return ;
    for(int i = 0; i < (int) screen.size(); i++)
    {
        if(screen[i] != nullptr)
        {
            delete screen[i];
            screen[i] = nullptr;
        }
    }
    screen.clear();
}

void MyWindow::shutdown()
{
    UImutex.lock();

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
    if(input != nullptr) 
    {
        delete input;
        input = nullptr;
    }
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;

    IMG_Quit();
    TTF_Quit();

    UImutex.unlock();
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
            if(input != nullptr) input->render();
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
    } else if(event.type == SDL_KEYDOWN) 
    {
        if(input != nullptr)
        {
            typing(event.key.keysym);
        }
    }
}

void MyWindow::typing(SDL_Keysym key)
{
    UImutex.lock();
    if(key.sym == SDLK_BACKSPACE)
        input->pop();
    else if(key.sym == SDLK_TAB)
        input->nextFocus();
    else if(key.sym >= SDLK_SPACE && key.sym <= SDLK_z)
        input->typing(key.sym);
    UImutex.unlock();
}

void MyWindow::action()
{
    while(isOpen())
    {
        while(SDL_PollEvent(&event))
            process();
    }
}
