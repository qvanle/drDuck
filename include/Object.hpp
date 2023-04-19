#ifndef OBJECT
#define OBJECT

#include <Sketch.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SYSTEM.hpp>
#include <SDL2/SDL_image.h>

class Object : public Sketch
{
private:
    SDL_Rect coor;
    bool visable;
    std::vector<SDL_Texture*> tes;
    SDL_Renderer* ren;
    int top;

    void initTextures(const json& mem);
    void initRect(const json& mem);
    void initVisible(const json& mem);

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
    const SDL_Rect &getCoor();
    bool isLiesInside(int x, int y);
    bool isLiesInside(int x, int y, int w, int h);
    bool isLiesInside(SDL_Rect rect);
    void addX(int k);
    void addY(int k);
    void addW(int k);
    void addH(int k);

    void show();
    void hide();
    bool isVisible();

    void setTextures(const json& mem);
    void pickTexure(int k);
    int size();

    void render(bool update);
    void moveTo(int x, int y, double time);
};

#endif
