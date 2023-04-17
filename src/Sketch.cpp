#include <Sketch.hpp>

Sketch::Sketch()
{
    font = nullptr;
    text = "";
    color = SDL_Color({0, 0, 0, 255});
    tes = nullptr;
    coor = SDL_Rect({0, 0, 0, 0});
    ren = nullptr;
}

void Sketch::clearTexture()
{
    if(tes == nullptr) return ;
    SDL_DestroyTexture(tes);
    tes = nullptr;
}

Sketch::~Sketch()
{
    font = nullptr;
    text.clear();
    clearTexture();
    ren = nullptr;
}

void Sketch::addChar(char ch)
{
    text = text + ch;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    clearTexture();
    tes = SDL_CreateTextureFromSurface(ren, surface);
    
    coor.w = surface->w;
    coor.h = surface->h;

    SDL_FreeSurface(surface);
}

void Sketch::popChar()
{
    if(text.empty()) return ;
    text.pop_back();
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    clearTexture();
    tes = SDL_CreateTextureFromSurface(ren, surface);

    coor.w = surface->w;
    coor.h = surface->h;

    SDL_FreeSurface(surface);
}

void Sketch::setText(std::string s)
{
    text = s;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    
    clearTexture();
    tes = SDL_CreateTextureFromSurface(ren, surface);

    coor.w = surface->w;
    coor.h = surface->h;

    SDL_FreeSurface(surface);
}

void Sketch::setColor(SDL_Color c)
{
    color = c;
}

void Sketch::setColor(int r, int g, int b, int a)
{
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
}

void Sketch::setCoor(int x, int y, int w, int h)
{
    coor = SDL_Rect({x, y, w, h});
}

void Sketch::setX(int x)
{
    coor.x = x;
}
void Sketch::setY(int y)
{
    coor.y = y;
}
void Sketch::setW(int w)
{
    coor.w = w;
}
void Sketch::setH(int h)
{
    coor.h = h;
}
void Sketch::setInCenterX(int x, int w)
{
    coor.x = x + (w - coor.w) / 2;
}
void Sketch::setInCenterY(int y, int h)
{
    coor.y = y + (h - coor.h) / 2;
}

void Sketch::setOnLeftSideX(int x, int w)
{
    coor.x = x;
}

void Sketch::setOnRightSideX(int x, int w)
{
    coor.x = x + w - coor.w;
}

void Sketch::setOnLeftSideY(int y, int h)
{
    coor.y = y;
}

void Sketch::setOnRightSideY(int y, int h)
{
    coor.y = y + h - coor.h;
}

void Sketch::render()
{
    SDL_RenderCopy(ren, tes, nullptr, &coor);
}

void Sketch::setRender(SDL_Renderer *&r)
{
    ren = r;
}

void Sketch::setBorder(int w, int r, int g, int b, int a)
{
    borderWidth = w;
    borderColor.r = r;
    borderColor.g = g;
    borderColor.b = b;
    borderColor.a = a;
}

void Sketch::FillWithColor()
{
    clearTexture();

    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, coor.w, coor.h, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_BLEND);

    SDL_FillRect(surf, nullptr, SDL_MapRGBA(surf->format, color.r, color.g, color.b, color.a));
    
    SDL_Rect borderRect;

    Uint32 c = SDL_MapRGBA(surf->format, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    borderRect = SDL_Rect({0, 0, borderWidth, coor.h});
    SDL_FillRect(surf, &borderRect, c);
    
    borderRect = SDL_Rect({0, 0, coor.w, borderWidth});
    SDL_FillRect(surf, &borderRect, c);

    borderRect = SDL_Rect({0, coor.h - borderWidth, coor.w, borderWidth});
    SDL_FillRect(surf, &borderRect, c);

    borderRect = SDL_Rect({coor.w - borderWidth, 0, borderWidth, coor.h});
    SDL_FillRect(surf, &borderRect, c);
    
    tes = SDL_CreateTextureFromSurface(ren, surf);

    SDL_FreeSurface(surf);

}

void Sketch::initRect(const json& mem)
{
    if(mem.contains("rect"))
    {
        if(mem["rect"].contains("x"))
        {
            coor.x = mem["rect"]["x"];
        }
        if(mem["rect"].contains("y"))
        {
            coor.y = mem["rect"]["y"];
        }
        if(mem["rect"].contains("w"))
        {
            coor.w = mem["rect"]["w"];
        }
        if(mem["rect"].contains("h"))
        {
            coor.h = mem["rect"]["h"];
        }
    }
}

void Sketch::initColor(const json& mem)
{
    if(mem.contains("color"))
    {
        if(mem["color"].contains("r"))
            color.r = mem["color"]["r"];
        if(mem["color"].contains("g"))
            color.g = mem["color"]["g"];
        if(mem["color"].contains("b"))
            color.b = mem["color"]["b"];
        if(mem["color"].contains("a"))
            color.a = mem["color"]["a"];
    }
}

void Sketch::initFont(const json& mem)
{
    if(mem.contains("font") && mem["font"].contains("name") && mem["font"].contains("size"))
    {
        char* name = combineLink(GLOBAL::FontsFolder, mem["font"]["name"].get<std::string>().c_str());
        if(font != nullptr) 
        {
            TTF_CloseFont(font);
            font = nullptr;
        }
        font = TTF_OpenFont(name, mem["font"]["size"]);
    }
}

void Sketch::init(const json &mem)
{
    
    initRect(mem);
    initColor(mem);
    initFont(mem);
    
    if(mem.contains("text"))
    {
        setText(mem["text"].get<std::string>());
    }
    if(mem.contains("fill with color"))
    {
        FillWithColor();
    }
}
