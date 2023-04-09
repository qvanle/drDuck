#include <Display.hpp>

Display::Display()
{
    ren = nullptr;
    Object::setCoor(0, 0, 960, 540);

    buts = nullptr;
    ButNum = 0;
    status = 0;
    freeze = false;
}

bool Display::isFocus()
{
    return status;
}

bool Display::changeFocus(int x, int y)
{
    if(isLiesInside(x, y))
    {
        status = 1;
        return true;
    }
    status = 0;
    return false;
}

void Display::init(const char *dir, const char *name)
{
    json mem; 

    readjson(dir, name, mem);

    init(mem[0]);
}

void Display::init(const json& mem)
{
    Object::init(mem, ren);   

    if(mem.contains("buttons"))
    {
        loadButtons(mem["buttons"]);
    }
    if(mem.contains("freeze"))
        freeze = mem["freeze"]; 
}

void Display::loadButtons(const json &mem)
{
    DeleteButs();

    ButNum = mem.size();

    buts = new Button*[ButNum];
    for(int i = 0; i < ButNum; i++)
    {
        buts[i] = nullptr;
        loadButton(buts[i], mem[i]);
    }            
}

void Display::setRenderer(SDL_Renderer* const& r)
{
    ren = r;
}

void Display::render() 
{
    if(!isVisible()) return ;
    Object::render(0);

    for(int i = 0; i < ButNum; i++)
        buts[i]->render();
}

void Display::render(bool update)
{
    Object::render(update);
    for(int i = 0; i < ButNum; i++)
        buts[i]->render(update);
}

void Display::DeleteButs()
{
    if(!isVisible()) return ;
    if(ButNum != 0)
    {
        delete [] buts;
        ButNum = 0;
    }
}

Display::~Display()
{

    ren = nullptr;
    Object::~Object();
    DeleteButs();
    freeze = false;
}


void Display::loadButton(Button *& but, const json& mem)
{

    if(but != nullptr)
    {
        delete but;
        but = nullptr;
    }

    but = new Button;
    but->setRenderer(ren);
    but->init(
            GLOBAL::AtrbButtons,
            mem["name"].get<std::string>().c_str()
            );
    but->init(mem);
    return ;
}

void Display::mouseMove(int x, int y)
{
    if(!isFocus()) return ;

    for(int i = 0; i < ButNum; i++)
        if(buts[i]->isChosen(x, y))
            break;
}

void Display::mousePressedButton(int x, int y, char*& MSG)
{
    if(!isFocus()) return ;
    for(int i = 0; i < ButNum; i++)
        if(buts[i]->isChosen(x, y))
        {
            MSG = buts[i]->getNextScreen();
        }
}

void Display::moveTo(int x, int y, double time)
{
    int dx = x - getCoor().x;
    int dy = y - getCoor().y;

    if(diff(time, 0))
    {
        addX(dx);
        addY(dy);

        for(int i = 0; i < ButNum; i++)
        {
            buts[i]->addX(dx);
            buts[i]->addY(dy);
        }
        return ;
    }

    double velo;

    if(abs(dx) < abs(dy))
        velo = dy / time;
    else velo = dx / time; 
       
    int loop = std::min(80.0, abs(velo * time));

    time = time / loop;  

    for(int i = 1; i <= loop; i++)
    {
        Uint32 startTime = SDL_GetTicks();

        addX(-dx * (i - 1) / loop);
        addX(dx * i / loop);
        addY(-dy * (i - 1) / loop);
        addY(dy * i / loop); 

        for(int j = 0; j < ButNum; j++)
        {
            buts[j]->addX(-dx * (i - 1) / loop);
            buts[j]->addX(dx * i / loop);
            buts[j]->addY(-dy * (i - 1) / loop);
            buts[j]->addY(dy * i / loop);
        }
        Uint32 deltatime = SDL_GetTicks() - startTime;
        SDL_Delay(time * 1000 - deltatime);
    }

}

void Display::trigger(int x, int y)
{
    if(isFreezed()) return ;
    if(!triggerable(x, y)) return ;

    if(!isVisible())
    {
        int dy = 100;
        addY(dy);
        for(int i = 0; i < ButNum; i++)
            buts[i]->addY(dy);
        show();
        moveTo(260, 440, 0.4);
    }
    if(!isFocus() && isVisible())
    {
        moveTo(260, 440, 0.4);
        hide();
    }
}

bool Display::isFreezed()
{
    return freeze;
}
