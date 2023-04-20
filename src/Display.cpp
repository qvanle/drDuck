#include <Display.hpp>

Display::Display()
{
    ren = nullptr;
    Object::setCoor(0, 0, 960, 540);

    buts.clear();
    status = 0;

    appear = 0;
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
    if(mem.contains("appear from"))
    {
        if(mem["appear from"].get<std::string>() == "bottom")
            appear = 1;
        else if(mem["appear from"].get<std::string>() == "right")
            appear = 2;
    }
}

void Display::loadButtons(const json &mem)
{
    DeleteButs();

    buts.resize(mem.size());

    for(int i = 0; i < (int) buts.size(); i++)
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

    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->render();
}

void Display::render(bool update)
{
    Object::render(update);
    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->render(update);
}

void Display::DeleteButs()
{
    if(!buts.empty())
    {
        for(int i = 0; i < (int) buts.size(); i++)
            delete buts[i];
        buts.clear();
    }
}

Display::~Display()
{

    ren = nullptr;
    //Object::~Object();
    DeleteButs();
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
    if(!isVisible()) return ;

    for(int i = 0; i < (int) buts.size(); i++)
        if(buts[i]->isChosen(x, y))
            break;
}

Button* Display::mousePressedButton(int x, int y)
{
    if(!isFocus()) return nullptr;
    for(int i = 0; i < (int) buts.size(); i++)
        if(buts[i]->isChosen(x, y))
        {
            return buts[i];
        }
    return nullptr;
}

void Display::appearFromBot(double time)
{
    int sy = getCoor().y;
    int dy = 540 - sy;
    
    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->addY(dy);

    setY(540);
    show();
    moveTo(getCoor().x, sy, time);
}

void Display::appearFromRight(double time)
{
    int sx = getCoor().x;
    int dx = 960 - sx; 

    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->addX(dx);

    setX(960);
    show();
    moveTo(sx, getCoor().y, time);
}

void Display::disappearToBot(double time)
{
    int sy = getCoor().y;
    int dy = sy - 540;
    show();
    moveTo(getCoor().x, 540, time);
    hide();
    setY(sy);
    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->addY(dy);
}

void Display::disappearToRight(double time)
{
    int sx = getCoor().x;
    int dx = sx - 960;
    show();
    moveTo(960, getCoor().y, time);
    hide();
    setX(sx);
    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->addX(dx);
}

int Display::getAppear()
{
    return appear;
}

void Display::moveTo(int x, int y, double time)
{
    int dx = x - getCoor().x;
    int dy = y - getCoor().y;

    if(diff(time, 0))
    {
        addX(dx);
        addY(dy);

        for(int i = 0; i < (int) buts.size(); i++)
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

        for(int j = 0; j < (int) buts.size(); j++)
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
    if(!isLiesInside(x, y)) return ;

    if(!isVisible())
    {
        int dy = 100;
        addY(dy);
        for(int i = 0; i < buts.size(); i++)
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

