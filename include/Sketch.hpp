#ifndef SKETCH 
#define SKETCH 

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_render.h>

#include <SYSTEM.hpp>

class Sketch
{
private: 

    SDL_Color borderColor;
    int borderWidth;

    TTF_Font* font;
    std::string text;

    SDL_Color color;
    
    SDL_Texture* tes;
    SDL_Rect coor;
    SDL_Renderer* ren;
    
    void clearTexture();

public:
    Sketch();
    ~Sketch();
    void setRender(SDL_Renderer *& r);
    void render();

    void setFont(TTF_Font *& f);
    
    void addChar(char ch);
    void popChar();
    void setText(std::string s);

    void setColor(SDL_Color c);
    void setColor(int r, int g, int b, int a);

    void setCoor(int x, int y, int w, int h);
    void setX(int x);
    void setY(int y);
    void setW(int w);
    void setH(int h);
    
    void setInCenterX(int x, int w);
    void setOnLeftSideX(int x, int w);
    void setOnRightSideX(int x, int w);

    void setInCenterY(int y, int h);
    void setOnLeftSideY(int y, int h);
    void setOnRightSideY(int y, int h);


    void setBorder(int w, int r, int g, int b, int a);

    void FillWithColor();
};

#endif
