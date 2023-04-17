#include <Sketch.hpp>

Sketch::Sketch()
{
    font = nullptr;
    text = "";
    color = SDL_Color({0, 0, 0, 255});
    fontColor = SDL_Color({255, 255, 255, 255});

    tes[0] = nullptr;
    tes[1] = nullptr;
    coor[0] = SDL_Rect({0, 0, 0, 0});
    coor[1] = coor[0];
    ren = nullptr;
}

void Sketch::clearTexture(int k)
{
    if(tes[k] == nullptr) return ;
    SDL_DestroyTexture(tes[k]);
    tes[k] = nullptr;
}

Sketch::~Sketch()
{
    font = nullptr;
    text.clear();
    clearTexture(0);
    clearTexture(1);
    ren = nullptr;
}

void Sketch::addChar(char ch)
{
    text = text + ch;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
    
    clearTexture(1);
    tes[1] = SDL_CreateTextureFromSurface(ren, surface);
    
    coor[1].w = surface->w;
    coor[1].h = surface->h;

    SDL_FreeSurface(surface);
}

void Sketch::popChar()
{
    if(text.empty()) return ;
    text.pop_back();
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
    
    clearTexture(1);
    tes[1] = SDL_CreateTextureFromSurface(ren, surface);

    coor[1].w = surface->w;
    coor[1].h = surface->h;

    SDL_FreeSurface(surface);
}

void Sketch::setText(std::string s)
{
    text = s;
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
    
    clearTexture(1);
    tes[1] = SDL_CreateTextureFromSurface(ren, surface);

    coor[1].w = surface->w;
    coor[1].h = surface->h;

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
    coor[0] = SDL_Rect({x, y, w, h});
}

void Sketch::setX(int x)
{
    coor[0].x = x;
}
void Sketch::setY(int y)
{
    coor[0].y = y;
}
void Sketch::setW(int w)
{
    coor[0].w = w;
}
void Sketch::setH(int h)
{
    coor[0].h = h;
}
void Sketch::setInCenterX()
{
    int x = coor[0].x;
    int w = coor[0].w;
    coor[1].x = x + (w - coor[1].w) / 2;
}
void Sketch::setInCenterY()
{
    int y = coor[0].y;
    int h = coor[0].h;
    coor[1].y = y + (h - coor[1].h) / 2;
}

void Sketch::setOnLeftSideX()
{
    coor[1].x = coor[0].x;
}

void Sketch::setOnRightSideX()
{
    int x = coor[0].x;
    int w = coor[0].w;
    coor[1].x = x + w - coor[1].w;
}

void Sketch::setOnLeftSideY()
{
    coor[1].y = coor[0].y;
}

void Sketch::setOnRightSideY()
{
    int y = coor[0].y;
    int h = coor[0].h;
    coor[1].y = y + h - coor[1].h;
}

void Sketch::render()
{
    std::cerr << (int) fontColor.a << "\n";
    SDL_RenderCopy(ren, tes[0], nullptr, &coor[0]);
    SDL_RenderCopy(ren, tes[1], nullptr, &coor[1]);
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
    int w = coor[0].w;
    int h = coor[0].h;
    clearTexture(0);

    SDL_Surface* surf = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_RGBA32);
    SDL_SetSurfaceBlendMode(surf, SDL_BLENDMODE_BLEND);

    SDL_FillRect(surf, nullptr, SDL_MapRGBA(surf->format, color.r, color.g, color.b, color.a));
    
    SDL_Rect borderRect;

    Uint32 c = SDL_MapRGBA(surf->format, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    borderRect = SDL_Rect({0, 0, borderWidth, h});
    SDL_FillRect(surf, &borderRect, c);
    
    borderRect = SDL_Rect({0, 0, w, borderWidth});
    SDL_FillRect(surf, &borderRect, c);

    borderRect = SDL_Rect({0, h - borderWidth, w, borderWidth});
    SDL_FillRect(surf, &borderRect, c);

    borderRect = SDL_Rect({w - borderWidth, 0, borderWidth, h});
    SDL_FillRect(surf, &borderRect, c);
    
    tes[0] = SDL_CreateTextureFromSurface(ren, surf);

    SDL_FreeSurface(surf);

}

void Sketch::initRect(const json& mem)
{
    if(mem.contains("rect"))
    {
        if(mem["rect"].contains("x"))
        {
            coor[0].x = mem["rect"]["x"];
        }
        if(mem["rect"].contains("y"))
        {
            coor[0].y = mem["rect"]["y"];
        }
        if(mem["rect"].contains("w"))
        {
            coor[0].w = mem["rect"]["w"];
        }
        if(mem["rect"].contains("h"))
        {
            coor[0].h = mem["rect"]["h"];
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
    if(!mem.contains("font")) return ;
    if(mem["font"].contains("name") && mem["font"].contains("size"))
    {
        char* name = combineLink(GLOBAL::FontsFolder, mem["font"]["name"].get<std::string>().c_str());
        if(font != nullptr) 
        {
            TTF_CloseFont(font);
            font = nullptr;
        }
        font = TTF_OpenFont(name, mem["font"]["size"]);
    }
    if(mem["font"].contains("rect"))
    {
        if(mem["font"]["rect"].contains("x"))
            coor[1].x = mem["font"]["rect"]["x"];
        if(mem["font"]["rect"].contains("y"))
            coor[1].y = mem["font"]["rect"]["y"];
    }
    if(mem["font"].contains("color"))
    {
        if(mem["font"]["color"].contains("r"))
        {
            fontColor.r = mem["font"]["color"]["r"];
        }
        if(mem["font"]["color"].contains("g"))
        {
            fontColor.g = mem["font"]["color"]["g"];
        }
        if(mem["font"]["color"].contains("b"))
        {
            fontColor.b = mem["font"]["color"]["b"];
        }
        if(mem["font"]["color"].contains("a"))
        {
            fontColor.a = mem["font"]["color"]["a"];
        }
    }
    if(mem["font"].contains("text"))
    {
        setText(mem["font"]["text"].get<std::string>());
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
