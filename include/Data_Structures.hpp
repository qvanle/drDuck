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
    std::vector<Sketch*> elements;
    int capacity;
    int num;
    int type;
    SDL_Renderer* ren;
    double speed;

    void StaticArrayCreate(std::string a);
    void StaticArrayInsert(int pos, std::string value);
    void StaticArrayErase(int pos); 
    void StaticArrayUpdate(int pos, int value);
    void StaticArraySearch(int value);


public:
    Data_Structures();
    ~Data_Structures();
    void setRender(SDL_Renderer *& r);
    void init(const json & mem);
    void initStaticArray(const json & mem);
    void loadValue(const json& mem);
    void render();
    void create(std::string s);
    void insert(int pos, std::string value);
    void erase(int pos);
    void update(int pos, int value);
    void search(int value);

};


#endif
