#ifndef OBJECT
#define OBJECT

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SYSTEM.hpp>
#include <SDL2/SDL_image.h>

class Object
{
private:
    SDL_Rect coor;    
    bool visable;
    SDL_Texture** tes;
    int tesSize;
    SDL_Renderer* ren;
    int top;

public:
    Object();
    ~Object();

    void clearTextures();

    void init(const json& mem, SDL_Renderer *& r);

    void setCoor(int x, int y, int w, int h);
    void setCoor(SDL_Rect key);
    void setX(int x);
    void setY(int y);
    void setW(int w);
    void setH(int h);
    SDL_Rect getCoor();
    bool isLiesInside(int x, int y);
    bool isLiesInside(int x, int y, int w, int h);
    bool isLiesInside(SDL_Rect rect);

    void show();
    void hide();
    bool isVisible();

    void setTextures(const json& mem);
    void pickTexure(int k);
    int size();

    void render(bool update);
};

#endif
