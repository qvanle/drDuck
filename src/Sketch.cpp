#include "SDL_pixels.h"
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

    borderWidth = 0;

    textAlignX = 2;
    textAlignY = 2;
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

void Sketch::createTextTexture()
{
    clearTexture(1);
    if(text.empty()) return ;

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fontColor);
    
    tes[1] = SDL_CreateTextureFromSurface(ren, surface);
    
    coor[1].w = surface->w;
    coor[1].h = surface->h;

    crop = coor[1];
    crop.x = 0;
    crop.y = 0;
    
    if(coor[1].w > coor[0].w || coor[1].h > coor[0].h)
    {
        crop = SDL_Rect({
                std::max(0, coor[1].w - coor[0].w), 
                std::max(0, coor[1].h - coor[0].h), 
                coor[0].w, 
                coor[0].h
            });
        coor[1].w = coor[0].w;
        coor[1].h = coor[0].h;
    }

    align();

    SDL_FreeSurface(surface);
}

void Sketch::addChar(char ch)
{
    text = text + ch;
    createTextTexture();
}

void Sketch::popChar()
{
    if(text.empty()) return ;
    text.pop_back();
    createTextTexture();
}

void Sketch::setText(std::string s)
{
    text = s;
    createTextTexture();
}

const std::string& Sketch::getText()
{
    return text;
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
    align();
}

void Sketch::setX(int x)
{
    coor[0].x = x;
    align();
}

void Sketch::addX(int x)
{
    coor[0].x += x;
    align();
}

void Sketch::addY(int y)
{
    coor[0].y += y;
    align();
}


void Sketch::setY(int y)
{
    coor[0].y = y;
    align();
}
void Sketch::setW(int w)
{
    coor[0].w = w;
    align();
}
void Sketch::setH(int h)
{
    coor[0].h = h;
    align();
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
    if(!isVisible()) return ;
    if(tes[0] != nullptr) SDL_RenderCopy(ren, tes[0], nullptr, &coor[0]);
    if(tes[1] != nullptr) SDL_RenderCopy(ren, tes[1], &crop, &coor[1]);
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

void Sketch::FillWithColor(SDL_Color c)
{
    SDL_Color temp = color;
    color = c;
    FillWithColor();
    color = temp;
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
        cache = color;
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
        if(mem["font"]["rect"].contains("align X"))
            textAlignX = mem["font"]["rect"]["align X"];
        if(mem["font"]["rect"].contains("align Y"))
            textAlignX = mem["font"]["rect"]["align Y"];
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

void Sketch::initBorder(const json& mem)
{
    if(!mem.contains("border")) return ;
    if(mem["border"].contains("width"))
        borderWidth = mem["border"]["width"];

    if(mem["border"].contains("color"))
    {
        if(mem["border"]["color"].contains("r"))
        {
            borderColor.r = mem["border"]["color"]["r"];
        }
        if(mem["border"]["color"].contains("g"))
        {
            borderColor.g = mem["border"]["color"]["g"];
        }
        if(mem["border"]["color"].contains("b"))
        {
            borderColor.b = mem["border"]["color"]["b"];
        }
        if(mem["border"]["color"].contains("a"))
        {
            borderColor.a = mem["border"]["color"]["a"];
        }
    }
}

void Sketch::init(const json &mem)
{
    
    initRect(mem);
    initColor(mem);
    initFont(mem);
    initBorder(mem);

    if(mem.contains("text"))
    {
        setText(mem["text"].get<std::string>());
    }
    if(mem.contains("visible"))
        visible = mem["visible"];
    if(mem.contains("fill with color"))
    {
        FillWithColor();
    }
}

void Sketch::align()
{

    if(textAlignX == 1) setOnLeftSideX();
    if(textAlignX == 2) setInCenterX();
    if(textAlignX == 3) setOnRightSideX();

    if(textAlignY == 1) setOnLeftSideY();
    if(textAlignY == 2) setInCenterY();
    if(textAlignY == 3) setOnRightSideY();
}

SDL_Rect Sketch::getCoor()
{
    return coor[0];
}

bool Sketch::isVisible()
{
    return visible;
}

void Sketch::show()
{
    visible = true;
}

void Sketch::hide()
{
    visible = false;
}

bool Sketch::isLieInside(int x, int y)
{
    if(x < coor[0].x || coor[0].x + coor[0].w <= x) return false;
    if(y < coor[0].y || coor[0].y + coor[0].y <= y) return false;
    return true;
}

void Sketch::moveTo(int x, int y, double time)
{
    int dx = x - getCoor().x;
    int dy = y - getCoor().y;
    
    if(diff(time, 0))
    {
        setX(x);
        setY(y);
        return ;
    }

    double velo;

    if(abs(dx) < abs(dy))
        velo = dy / time;
    else velo = dx / time;  
     
    int loop = std::min(80.0, abs(velo * time));

    time = time / loop; 
    
    for(int i = 0; i <= loop; i++)
    {
        Uint32 startTime = SDL_GetTicks();

        addX(-dx * (i - 1) / loop);
        addX(dx * i / loop);
        addY(-dy * (i - 1) / loop);
        addY(dy * i / loop);
        render(); 
        Uint32 deltaTime = SDL_GetTicks() - startTime;
        startTime = SDL_GetTicks();
        if(deltaTime <= time * 1000)
            SDL_Delay(time * 1000 - deltaTime);
    }
}

void Sketch::highight()
{
    color.r = 255 - color.r;
    color.g = 255 - color.g;
    color.b = 255 - color.g;
    if(color.r > 20 && color.g > 20 && color.b > 20)
    {
        color.r -= color.r * 0.3;
        color.g -= color.g * 0.3;
        color.b -= color.b * 0.3;
    }
    FillWithColor();
}

void Sketch::unHighlight()
{
    color = cache;
    FillWithColor();
}
