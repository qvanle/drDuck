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
    int step;
    bool finish;
    std::mutex stepMutex;

    void initStaticArray(const json & mem);
    void StaticArrayCreate(std::string s);
    void StaticArrayInsert(int pos, int value, std::mutex & m);
    void StaticArrayErase(int pos, std::mutex & m); 
    void StaticArrayUpdate(int pos, int value, std::mutex & m);
    void StaticArraySearch(int value, std::mutex & m);


    void initDynamicArray(const json & mem);
    void DynamicArrayCreate(std::string s);
    void DynamicArrayInsert(int pos, int value, std::mutex & m);
    void DynamicArrayErase(int pos, std::mutex & m);
    void DynamicArrayUpdate(int pos, int value, std::mutex & m);
    void DynamicArraySearch(int value, std::mutex & m);


public:

    bool isFinish();
    void setStep(int k);
    void decStep();
    int getStep();
    int size();
    Data_Structures();
    ~Data_Structures();

    void speedUp();
    void slowDown();
    void nextStep();

    void setRender(SDL_Renderer *& r);
    void init(const json & mem);
    void loadValue(const json& mem);
    void render();
    void render(bool update);
    void create(std::string s);
    void insert(std::string s1, std::string s2, std::mutex & m);
    void erase(std::string s1, std::mutex & m);
    void update(std::string s1, std::string s2, std::mutex & m);
    void search(std::string s2, std::mutex & m);

};


#endif
