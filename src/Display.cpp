#include <Display.hpp>

Display::Display()
{
    background = nullptr;
    renderer = nullptr;

    coor.x = 0;
    coor.y = 0;
    coor.w = 960;
    coor.h = 540;
    buts = nullptr;
    ButNum = 0;
}

void Display::init(const char *dir, const char *name)
{

    char* link = combineLink(dir, name);
    std::ifstream fin(link);

    if(!fin.is_open()) return ; 

    json mem; 

    fin >> mem;

    fin.close();

    delete [] link;

    if(mem.contains("background"))
    {
        loadBackground(mem["background"]);
    }

    if(mem.contains("buttons"))
    {
        ButNum = mem["buttons"].size();
        buts = new Button*[ButNum];
        for(int i = 0; i < ButNum; i++)
        {
            loadButton(buts[i], mem["buttons"][i]);
        }
    }
}

void Display::loadBackground(const json& mem)
{
    if(!mem.contains("name") || !mem.contains("type"))
    {
        return ;
    }
    std::string type = mem["type"].get<std::string>();    

    char* name = combineName(
        mem["name"].get<std::string>().c_str(),
        type.c_str()
    );

    char* link = combineLink(
        GLOBAL::BackgroundFolder, 
        name
    );

    delete [] name;

    SDL_Surface* surf;

    if(type == "bmp")
        surf = SDL_LoadBMP(link);
    else surf = IMG_Load(link);

    background = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);
    delete [] link;
    
    if(!mem.contains("rect"))
    {
        return ;
    }

    coor.x = mem["rect"]["x"];
    coor.y = mem["rect"]["y"];
    coor.w = mem["rect"]["w"];
    coor.h = mem["rect"]["h"];
}

void Display::setRenderer(SDL_Renderer* const& ren)
{
    renderer = ren;
}

void Display::render() 
{
    SDL_RenderCopy(renderer, background, nullptr, &coor);

    for(int i = 0; i < ButNum; i++)
        buts[i]->render();
}
Display::~Display()
{
    SDL_DestroyTexture(background);
    renderer = nullptr;
    coor.x = 0;
    coor.y = 0;
    coor.w = 0;
    coor.h = 0;

    if(buts != nullptr)
    {
        for(int i = 0; i < ButNum; i++)
            delete buts[i];
        delete [] buts;
        ButNum = 0;
    }
}


void Display::loadButton(Button *& but, const json& mem)
{
    but = new Button;
    but->setRenderer(renderer);
    but->init(
                GLOBAL::AtrbButtons,
                mem["name"].get<std::string>().c_str()
            );
    but->init(mem);
    return ;
}

void Display::mouseMove(int x, int y)
{
    for(int i = 0; i < ButNum; i++)
        if(buts[i]->isChosen(x, y))
            break;
}

void Display::mousePressedButton(int x, int y, char*& MSG)
{
    for(int i = 0; i < ButNum; i++)
        if(buts[i]->isPressed(x, y))
        {
            MSG = buts[i]->getNextScreen();
        }
}
