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
}

void Button::init(const char* name)
{
    const char* fullname = combineName(name, "json");
    init(GLOBAL::AtrbButtons, fullname);

    delete [] fullname;
}
int Button::size()
{
    return SizeOfGrains;
}

void Button::init(const char* dir, const char* name)
{
    char* link = combineLink(dir, name);
    std::ifstream fin(link);

    json mem; 

    fin >> mem;
    fin.close();
    delete [] link;

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
        coor.x = mem["rect"]["x"];
        coor.y = mem["rect"]["y"];
        coor.w = mem["rect"]["w"];
        coor.h = mem["rect"]["h"];
    }
}

void Button::setRenderer(SDL_Renderer* const& ren)
{
    renderer = ren;
}

void Button::render()
{
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
