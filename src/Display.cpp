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

    delete [] link;

    if(!fin.is_open()) return ; 

    json mem; 

    fin >> mem;

    fin.close();
   
    if(mem.contains("background"))
    {
        loadBackground(mem["background"]);
    }

    if(mem.contains("buttons"))
    {
        DeleteButs();

        ButNum = mem["buttons"].size();

        buts = new Button*[ButNum];
        for(int i = 0; i < ButNum; i++)
        {
            buts[i] = nullptr;
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

    SDL_Surface* surf;

    if(type == "bmp")
        surf = SDL_LoadBMP(link);
    else surf = IMG_Load(link);

    if(background != nullptr)
    {
        SDL_DestroyTexture(background);
        background = nullptr;
    }
    background = SDL_CreateTextureFromSurface(renderer, surf);
    
    if(mem.contains("rect")) 
    {
        if(mem["rect"].contains("x"))
            coor.x = mem["rect"]["x"];
        if(mem["rect"].contains("y"))
            coor.y = mem["rect"]["y"];
        if(mem["rect"].contains("w"))
            coor.w = mem["rect"]["w"];
        if(mem["rect"].contains("h"))
            coor.h = mem["rect"]["h"];
    }
    SDL_FreeSurface(surf);
    delete [] name;
    type.clear();
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

void Display::DeleteButs()
{

    if(ButNum != 0)
    {
        delete [] buts;
        ButNum = 0;
    }
}

Display::~Display()
{

    if(background != nullptr )
    {    
        SDL_DestroyTexture(background);
        background = nullptr;
    }

    renderer = nullptr;

    coor.x = 0;
    coor.y = 0;
    coor.w = 0;
    coor.h = 0;

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
