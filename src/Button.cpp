#include <Button.hpp>

Button::Button()
{
    ren = nullptr;
    nextScreen = nullptr;
}

bool Button::isChosen(int x, int y)
{
    if(!isLiesInside(x, y))
    {
        pickTexure(0);
        return false;
    }
    pickTexure(1);
    return true;
}

void Button::init(const char* name)
{
    init(GLOBAL::AtrbButtons, name);
}

void Button::init(const char* dir, const char* name)
{
    char* fullname = combineName(name, "json");
    char* link = combineLink(dir, fullname);
    std::ifstream fin(link);

    json mem; 

    fin >> mem;
    fin.close();
   
    init(mem);

    delete [] fullname;
    delete [] link;
}

void Button::init(const json& mem)
{
    Object::init(mem, ren);

    if(mem.contains("next screen"))
    {
        std::string s = mem["next screen"].get<std::string>();
        nextScreen = new char[s.size() + 2];
        strcpy(nextScreen, s.c_str());

        s.clear();
    }
}

void Button::setRenderer(SDL_Renderer* const& r)
{
    ren = r;
}

void Button::render()
{
    if(!isVisible()) return ;

    Object::render(0);
    return ;
}
void Button::render(bool update)
{
    if(!isVisible()) return ;
    Object::render(update);
    return ;
}

char* const& Button::getNextScreen()
{
    return nextScreen;
}

void Button::Delete()
{
    ren = nullptr;
    Object::~Object();
    
    if(nextScreen != nullptr) 
        delete [] nextScreen;
}

Button::~Button()
{
    Delete();
}
