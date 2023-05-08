#include <Display.hpp>
/**
 * @brief Constructor of Display
*/
Display::Display()
{
    ren = nullptr;
    Object::setCoor(0, 0, 960, 540);

    buts.clear();
    status = 0;

    appear = 0;
}
/**
 * @brief return true if user are iteractive on this display
*/
bool Display::isFocus()
{
    return status;
}
/**
 * @brief set this display to be iteractive or not by mouse move
 * @param x x coordinate of mouse
 * @param y y coordinate of mouse
*/
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
/**
 * @brief init this display by json file which is in dir/name
 * @param dir directory of json file
 * @param name name of json file
*/
void Display::init(const char *dir, const char *name)
{
    json mem; 

    readjson(dir, name, mem);

    init(mem[0]);
}
/**
 * @brief init this display by json file
 * @param mem json file
 * init buttons, animation (if it has)
*/
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
/**
 * @brief load buttons from json file
 * @param mem json file
*/
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
/**
 * @brief set renderer for this display
 * @param &r renderer
*/
void Display::setRenderer(SDL_Renderer* const& r)
{
    ren = r;
}
/**
 * @brief render this display
*/
void Display::render() 
{
    if(!isVisible()) return ;
    Object::render(0);

    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->render();
}
/**
 * @brief render this display
 * @param update boolean 
 * if update is true, it will display to screen after render it
*/
void Display::render(bool update)
{
    Object::render(update);
    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->render(update);
}
/**
 * @brief delete all buttons
*/
void Display::DeleteButs()
{
    if(!buts.empty())
    {
        for(int i = 0; i < (int) buts.size(); i++)
            delete buts[i];
        buts.clear();
    }
}
/**
 * @brief set button visible to false
 * @param k index of button
*/
void Display::hideButton(int k)
{
    if(k >= (int) buts.size()) return ;
    buts[k]->hide();
}
/**
 * @brief set button visible to true
 * @param k index of button
*/
void Display::showButton(int k)
{
    if(k >= (int) buts.size()) return ;
    buts[k]->show();
}

Display::~Display()
{

    ren = nullptr;
    //Object::~Object();
    DeleteButs();
}

/**
 * @brief load button from json file
 * @param but button that will be loaded
 * @param mem json file
*/
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
/**
 * @brief handle mouse move event
 * @param x x coordinate of mouse
 * @param y y coordinate of mouse
 * if mouse is on button, it will change button's texture (if it has) and status
*/
void Display::mouseMove(int x, int y)
{
    if(!isFocus()) return ;
    if(!isVisible()) return ;

    for(int i = 0; i < (int) buts.size(); i++)
        if(buts[i]->isChosen(x, y))
            break;
}
/**
 * @brief get the button that is pressed
 * @param x x coordinate of mouse
 * @param y y coordinate of mouse
 * @return button that is pressed or nullptr if no button is pressed
*/
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
/**
 * @brief move the display to (x, y) coordinate in time (second) from the bottom
 * @param time time double
*/
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
/**
 * @brief move the display to (x, y) coordinate in time (second) from the right
 * @param time time double
*/
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

/**
 * @brief move the display to bottom coordinate in time (second) from the current position
 * @param time time double
*/
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
/**
 * @brief move the display to right coordinate in time (second) from the current position
 * @param time time double
*/
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
/**
 * @brief return true if the screen have animation
*/
int Display::getAppear()
{
    return appear;
}
/**
 * @brief move the display to (x, y) coordinate in time (second) from the current position
*/
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
/**
 * @brief Run animation when mouse is in trigger area of screen
 * @param x x coordinate of mouse
 * @param y y coordinate of mouse
*/
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

