#include <DuckWin.hpp>
/**
 * @brief contructor of MyWindow
*/
MyWindow::MyWindow()
{
    soundMutex.lock();
    status = 0;
    WIDTH = 0;
    HEIGHT = 0;
    window = nullptr;
    renderer = nullptr;
    FocusOn = 0;
    screen.clear();
    DT = nullptr;
    input = nullptr;
    turnOn = true;
    soundOn = true;
}

/**
 * @brief init the window 
 * default size is 960x540
 * 
 * default fps is 60
 * 
 * default sound is on
 * 
 * default status is 1
 * 
 * init window, renderer, audio, image, font
*/
void MyWindow::init()
{
    status = 1;
    WIDTH = 960;
    HEIGHT = 540;
    RANDOM::init();

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
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


    audioSpec.freq = 44100; 
    audioSpec.format = AUDIO_S16SYS; 
    audioSpec.channels = 2;
    audioSpec.samples = 1024;
    SDL_OpenAudio(&audioSpec, NULL);
    SDL_AudioSpec waveSpec;
    SDL_LoadWAV((GLOBAL::SoundFolder + "quark.wav").c_str(), &waveSpec, &waveBuffer, &waveLength);
}

/**
 * @brief when user move mouse, this function will be called
 * @param x x coordinate of mouse
 * @param y y coordinate of mouse
 * When mouse is move it will trigger the button, screen.
*/
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

/**
 * @brief The same to MyWindow::isChangeScreen(Button *& but) but source DT from json
 * @param but button that through from system or click by user
 * @param mem json that contain information of data structure
*/
bool MyWindow::isChangeScreen(Button *& but, const json &mem)
{
    if(but->getAction() == "change screen")
    {
        UImutex.lock();

        if(input != nullptr && input->isVisible())
        {
            delete input;
        }
        if(DT != nullptr && DT->isVisible() && DT->isFinish())
        {
            DT->hide();
        }else {

            std::string type = but->getDataStructure();
            std::string screenName = but->getNextScreen();

            if(DT != nullptr && !DT->isFinish()) 
            {
                UImutex.unlock();
                return true;
            }
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
            }else if(type == "DoublyLinkedList.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "CircularLinkedList.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "Stack.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "Queue.json")
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
        if(DT != nullptr)
        {
            DT->loadValue(mem);
            DT->show();
        }
        UImutex.unlock();
        return true;
    }else if(but->getAction() == "open file")
    {
        UImutex.lock();
        if(input != nullptr) delete input;
        input = new InputBox;
        json mem;
        readJson(GLOBAL::AtrbInputBox + "open.json", mem);
        input->setRender(renderer);
        input->init(mem);
        UImutex.unlock();
        return true;
    }
    return false;
}
/**
 * @brief delete all screen and add new screens which information can be found from the button pressed
 * @param but button that through from system or click by user
*/
bool MyWindow::isChangeScreen(Button *& but)
{
    if(but->getAction() == "change screen")
    {
        UImutex.lock();

        if(input != nullptr && input->isVisible())
        {
            delete input;
        }
        if(DT != nullptr && DT->isVisible() && DT->isFinish())
        {
            DT->hide();
        }else {

            std::string type = but->getDataStructure();
            std::string screenName = but->getNextScreen();
            if(DT != nullptr && !DT->isFinish()) 
            {
                UImutex.unlock();
                return true;
            }

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
            }else if(type == "DoublyLinkedList.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "CircularLinkedList.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "Stack.json")
            {
                DT = new Data_Structures;
                DT->setRender(renderer);
                json mem;
                readJson(GLOBAL::AtrbDT + type, mem);
                DT->init(mem);
            }else if(type == "Queue.json")
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
    }else if(but->getAction() == "open file")
    {
        UImutex.lock();
        if(input != nullptr) delete input;
        input = new InputBox;
        json mem;
        readJson(GLOBAL::AtrbInputBox + "open.json", mem);
        input->setRender(renderer);
        input->init(mem);
        UImutex.unlock();
        return true;
    }
    return false;
}
/**
 * @brief Action on data structure when user pressed button
 * @param but button that through from system or click by user
 * Action is insert, delete, search, update, new, push, pop
 * @return true if action is done, false if not
*/
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
        if(DT != nullptr && (DT->getType() == 6 || DT->getType() == 7)) 
            readJson(GLOBAL::AtrbInputBox + "pop.json", mem);
        else readJson(GLOBAL::AtrbInputBox + "delete.json", mem);
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
        if(DT != nullptr && (DT->getType() == 6 || DT->getType() == 7)) 
            readJson(GLOBAL::AtrbInputBox + "push.json", mem);
        else 
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
/**
 * @brief Action on input box 
 * @param but button that through from system or click by user
*/
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
    if(but->getAction() == "done setting")
    {
        UImutex.lock();
        DT->custom(input->getText(0), input->getText(1), input->getText(2), input->getText(3));
        delete input;
        input = nullptr;
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "done open")
    {
        UImutex.lock();
        std::string filename = "saving/" + input->getText(0) + ".json";
        delete input;
        input = nullptr;
        if(DT != nullptr) delete DT;
        DT = nullptr;
        UImutex.unlock();
        if(!std::filesystem::exists(filename)) return true; 
        json F1;
        readJson(filename, F1);

        Button* but = new Button;
        but->setDataStructure(F1["name"].get<std::string>());
        isChangeScreen(but, F1);

        delete but;
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
    if(but->getAction() == "done push")
    {
        UImutex.lock();
        input->hide();
        std::string s = input->getText(1);
        UImutex.unlock();
        std::thread push(&Data_Structures::push, DT, s, std::ref(UImutex));
        push.detach();
    }
    if(but->getAction() == "done pop")
    {
        UImutex.lock();
        std::string s = input->getText(0);
        input->hide();
        UImutex.unlock();
        std::thread pop(&Data_Structures::pop, DT, s, std::ref(UImutex));
        pop.detach();
    }
    if(but->getAction() == "random color 1")
    {
        UImutex.lock();
        std::string r = std::to_string(RANDOM::getInt(0, 255));
        std::string g = std::to_string(RANDOM::getInt(0, 255));
        std::string b = std::to_string(RANDOM::getInt(0, 255));
        input->setFocus(0);
        input->setInput(r + ", " + g + ", " + b);
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "random color 2")
    {
        UImutex.lock();
        std::string r = std::to_string(RANDOM::getInt(0, 255));
        std::string g = std::to_string(RANDOM::getInt(0, 255));
        std::string b = std::to_string(RANDOM::getInt(1, 255));
        input->setFocus(1);
        input->setInput(r + ", " + g + ", " + b);
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "random color 3")
    {
        UImutex.lock();
        std::string r = std::to_string(RANDOM::getInt(0, 255));
        std::string g = std::to_string(RANDOM::getInt(0, 255));
        std::string b = std::to_string(RANDOM::getInt(1, 255));
        input->setFocus(2);
        input->setInput(r + ", " + g + ", " + b);
        UImutex.unlock();
        return true;
    }
    if(but->getAction() == "random color 4")
    {
        UImutex.lock();
        std::string r = std::to_string(RANDOM::getInt(0, 255));
        std::string g = std::to_string(RANDOM::getInt(0, 255));
        std::string b = std::to_string(RANDOM::getInt(1, 255));
        input->setFocus(3);
        input->setInput(r + ", " + g + ", " + b);
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
    if(but->getAction() == "all")
    {
        UImutex.lock();
        input->setFocus(0);
        input->setInput(std::to_string(DT->size()));
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
/**
 * @brief Action on play buttons
 * @param but button that was clicked
 * Action is slow down, speed up, play, pause, next step
*/
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
/**
 * @brief When user press mouse, this function will be called to handle it
 * @param x x coordinate of mouse
 * @param y y coordinate of mouse 
*/
void MyWindow::mousePress(int x, int y)
{

    if(input != nullptr) input->mousePress(x, y);

    Button* but = nullptr;

    if(input != nullptr) 
    {
        but = input->getButtonPressedByMouse(x, y); 
    }
    if(but == nullptr) 
    {
        but = top()->mousePressedButton(x, y);
    }
    if(but == nullptr) return ;

    if(but->getAction() == "setting")
    {
        UImutex.lock();
        json mem;
        readJson(GLOBAL::AtrbInputBox + "setting.json", mem);
        if(input != nullptr) delete input;
        input = new InputBox;
        input->setRender(renderer);
        input->init(mem);
        UImutex.unlock();
        return ;
    }

    if(but->getAction() == "sound on") 
    {
        turnOn = true;
        screen[0]->hideButton(0);
        screen[0]->showButton(1);
        return ;
    }
    if(but->getAction() == "sound off") 
    {
        turnOn = false;
        screen[0]->hideButton(1);
        screen[0]->showButton(0);
        return ;
    }
    soundOn = turnOn;
    soundMutex.unlock();
    if(soundOn) SDL_Delay(350);
    else SDL_Delay(100);
    soundMutex.lock();
    if(isChangeScreen(but)) 
    {
        return ;
    }
    if(isDToperator(but)) 
    {
        return;
    }
    if(isInputButton(but)) 
    {
        return ;
    }
    if(isPlayButton(but))
    {
        return ;
    }
}

/**
 * @brief delete all screens
*/
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
/** 
 * @brief Turn off MyWindow 
*/
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
    soundMutex.unlock();
} 
/**
 * @brief Return true if MyWindow is open, false otherwise
*/
bool MyWindow::isOpen()
{
    return status == 1;
}

bool MyWindow::isHanging()
{
    return status == 2;
}
/**
 * @brief Return true if MyWindow is close, false otherwise
*/
bool MyWindow::isClose()
{
    return status == 0;
}
/**
 * @brief Delete all screens and add new screens which information is in json file have directory is "GLOBAL::AtrbScreens/name"
*/
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
    if(turnOn)
    {
        screen[0]->hideButton(0);
        screen[0]->showButton(1);
    }else 
    {
        screen[0]->hideButton(1);
        screen[0]->showButton(0);
    }
    FocusOn = 0;
}
/**
 * @brief Return the screen that is focus on
*/
Display *& MyWindow::top()
{
    return screen[FocusOn];
}
MyWindow::~MyWindow()
{
    shutdown();
}
/**
 * @brief Start MyWindow
 * render and sound, user input will be run in 3 thread
*/
void MyWindow::run()
{
    std::thread draw(&MyWindow::render, this);
    std::thread sound(&MyWindow::speak, this);
    action();

    draw.join();
    sound.join();
}
/**
 * @brief render function
*/
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
/**
 * @brief sound function
*/
void MyWindow::speak()
{
    while(isOpen())
    {
        if(soundMutex.try_lock())
        {
            if(soundOn)
            {
                SDL_QueueAudio(1, waveBuffer, waveLength);
                SDL_PauseAudio(0); 
            }
            soundOn = false;
            soundMutex.unlock();
        }
    }
}
/**
 * @brief Handle user input
*/
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
/**
 * @brief add a character to input box
*/
void MyWindow::typing(SDL_Keysym key)
{
    UImutex.lock();
    if(key.sym == SDLK_BACKSPACE)
        input->pop();
    else if(key.sym == SDLK_TAB)
        input->nextFocus();
    else if(key.sym >= SDLK_a && key.sym <= SDLK_z)
    {
        char value = key.sym;
        if(((SDL_GetModState() & KMOD_CAPS) != 0) ^ ((SDL_GetModState() & KMOD_SHIFT) != 0)) 
            value = 'A' + (value - SDLK_a);
        input->typing(value);
    }else if(key.sym >= SDLK_SPACE && key.sym < SDLK_a)
    {
        char value = key.sym;
        if(event.key.keysym.sym == SDLK_MINUS && (SDL_GetModState() & KMOD_SHIFT))
            value = '_';
        input->typing(value);
    }
    UImutex.unlock();
}
/**
 * @brief get user input
*/
void MyWindow::action()
{
    while(isOpen())
    {
        while(SDL_PollEvent(&event))
            process();
    }
}
