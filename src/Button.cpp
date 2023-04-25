#include <Button.hpp>

Button::Button()
{
    ren = nullptr;
    msg = nullptr;
    argc = 0;
    argv.clear();
}

bool Button::isChosen(int x, int y)
{
    if(!isVisible() || !isLiesInside(x, y))
    {
        pickTexure(0);
        return false;
    }
    pickTexure(1);
    return true;
}

std::string Button::getAction()
{
    return action;
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

    if(mem.contains("action"))
    {
        action = mem["action"].get<std::string>();
        if(mem.contains("msg"))
        {
            std::string s = mem["msg"].get<std::string>();
            msg = new char[s.size() + 2];
            strcpy(msg, s.c_str());
            s.clear();
        }
        if(mem.contains("arg"))
        {
            argc = mem["arg"].size();
            argv.resize(argc);
            for(int i = 0; i < argc; i++)
            {
                std::string s = mem["arg"][i].get<std::string>();
                argv[i] = new char[s.size() + 2];
                strcpy(argv[i], s.c_str());
                s.clear();
            }
        }
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
    return msg;
}

void Button::Delete()
{
    ren = nullptr;
    //Object::~Object();

    if(msg != nullptr) 
        delete [] msg;

    if(!argv.empty())
    {
        for(int i = 0; i < argc; i++)
            delete [] argv[i];
        argv.clear();
        argc = 0;
    }
}

Button::~Button()
{
    Delete();
}

std::string Button::getDataStructure()
{
    if(action != "change screen") return "";
    if((std::string)(msg) != "working.json") return "";
    if(argc == 0) return "";
    return argv[0];
}

void Button::setDataStructure(std::string s)
{
    action = "change screen";

    if(msg != nullptr) delete msg;
    for(int i = 0; i < argv.size(); i++) delete [] argv[i];
    argv.clear();

    std::string screen = "working.json";
    msg = new char[screen.size() + 1];
    for(int i = 0; i < screen.size(); i++)
        msg[i] = screen[i];

    argv.resize(1);
    argc = 1;
    argv[0] = new char [s.size() + 1];

    for(int i = 0; i < s.size(); i++)
        argv[0][i] = s[i];
}
