#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

#include <SDL2/SDL.h>
#include <SDL_render.h>

#include <Display.hpp>
#include <Object.hpp>
#include <SYSTEM.hpp>
#include <Sketch.hpp>

class Data_Structures : public Sketch
{
private: 
    Sketch ** elements;
    int capacity;
    int num;
    int type;
    SDL_Renderer* ren;

public:
    Data_Structures();
    ~Data_Structures();
    void setRender(SDL_Renderer *& r);
    void init(const json & mem);
    void initStaticArray(const json & mem);
    void loadValue(const json& mem);
    void render();
};


#endif
