#include <Button.hpp>

Button::Button()
{
    grains = nullptr;
    renderer = nullptr;
    SizeOfGrains = 0;
    coor.x = 0;
    coor.y = 0;
    coor.w = 0;
    coor.h = 0;
    status = 0;
    visible = false;
}
void Button::show()
{
    visible = true;
}
void Button::hide()
{
    visible = false;
}
void Button::nxStatus()
{
    status = (status + 1) % size();
}
void Button ::pvStatus()
{
    status = (status + size() - 1) % size();
}

bool Button::isChosen(int x, int y)
{
    if(x < coor.x || coor.x + coor.w <= x) return true;
    if(y < coor.y || coor.y + coor.h <= y) return false;
    if(!visible) return false;
    return true;
}

void Button::init(const char* name)
{
    init(GLOBAL::AtrbButtons, name);
}
int Button::size()
{
    return SizeOfGrains;
}

void Button::init(const char* dir, const char* name)
{
    char* fullname = combineName(name, "json");
    char* link = combineLink(dir, fullname);
    delete [] fullname;
    std::ifstream fin(link);

    delete [] link;

    json mem; 

    fin >> mem;
    fin.close();
   
    init(mem);
}

void Button::setTextures(const json& mem)
{
    clearTextures();

    SizeOfGrains = mem["textures"].size();
    grains = new SDL_Texture*[SizeOfGrains];

    char* FolderName = new char [256];
    strcpy(FolderName, mem["name"].get<std::string>().c_str());
    for(int i = 0 ; i < size(); i++)
    {
        const char* fullname = combineName(
            mem["textures"][i]["name"].get<std::string>().c_str(),
            mem["textures"][i]["type"].get<std::string>().c_str()
        );
        const char* name = combineLink( 
            FolderName,
            fullname
        );
        
        delete []fullname;

        const char* link = combineLink(
            GLOBAL::ButtonFolder, 
            name
        ); 
        delete [] name;
        
        SDL_Surface* surf = SDL_LoadBMP(link);
        
        grains[i] = SDL_CreateTextureFromSurface(renderer, surf);
        
        SDL_FreeSurface(surf);

        delete [] link;
    }
    delete [] FolderName;
}

void Button::init(const json& mem)
{
    if(mem.contains("textures"))
    {
        setTextures(mem);
    }
    if(mem.contains("rect"))
    {
        if(mem["rect"].contains("x")) 
            coor.x = mem["rect"]["x"];
        if(mem["rect"].contains(("y")))
            coor.y = mem["rect"]["y"];
        if(mem["rect"].contains("w"))
            coor.w = mem["rect"]["w"];
        if(mem["rect"].contains("h"))
            coor.h = mem["rect"]["h"];
    }
    if(mem.contains("visible"))
    {
        visible = mem["visible"];
    }
}

void Button::setRenderer(SDL_Renderer* const& ren)
{
    renderer = ren;
}

void Button::render()
{
    if(!visible) return ;
    SDL_RenderCopy(renderer, grains[status], nullptr, &coor);
    return ;
}

void Button::clearTextures()
{
    if(grains != nullptr)
    {
        for(int i = 0; i < size(); i++)
        {
            if(grains[i] != nullptr) 
                SDL_DestroyTexture(grains[i]);
        }
        delete [] grains;
        grains = nullptr;
        SizeOfGrains = 0;
    }

}

void Button::Delete()
{
    clearTextures();
    if(renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    
    coor.x = 0;
    coor.y = 0;
    coor.h = 0;
    coor.w = 0;
}

Button::~Button()
{
    Delete();
}
