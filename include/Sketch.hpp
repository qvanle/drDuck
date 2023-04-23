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

    bool visible;

    int textAlignX;
    int textAlignY;

    SDL_Color borderColor;
    int borderWidth;

    TTF_Font* font;
    SDL_Color fontColor;
    std::string text;
    SDL_Rect crop;
    
    SDL_Color color;
    SDL_Color cache;
    SDL_Texture* tes[2];
    SDL_Rect coor[2];
    SDL_Renderer* ren;
protected: 
    void clearTexture(int k);

    void initRect(const json& mem);
    void initColor(const json& mem);
    void initFont(const json& mem);
    void initBorder(const json& mem);

    void createTextTexture();

public:
    Sketch();
    ~Sketch();

    bool isVisible();

    void show();
    void hide();

    void init(const json& mem);

    void setRender(SDL_Renderer *& r);
    void render();

    void addChar(char ch);
    void popChar();
    void setText(std::string s);
    const std::string & getText();

    void setColor(SDL_Color c);
    void setColor(int r, int g, int b, int a);

    void setCoor(int x, int y, int w, int h);
    void setX(int x);
    void setY(int y);
    void setW(int w);
    void setH(int h);
    void addX(int x);
    void addY(int y);
    
    void setInCenterX();
    void setOnLeftSideX();
    void setOnRightSideX();

    void setInCenterY();
    void setOnLeftSideY();
    void setOnRightSideY();

    void align();
    SDL_Rect getCoor();

    void setBorder(int w, int r, int g, int b, int a);

    void FillWithColor();
    void FillWithColor(SDL_Color c);
    void highlight();
    void unHighlight();

    bool isLieInside(int x, int y);

    void moveTo(int x, int y, double time);
};

#endif
