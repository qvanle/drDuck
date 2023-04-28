#ifndef PSEUDOCODE 
#define PSEUDOCODE

#include <SYSTEM.hpp>
#include <Sketch.hpp>
#include <SDL2/SDL.h>
#include <Object.hpp>


class Script : public Sketch
{
private:
    vector<Sketch*> lines;
    Object* obj;
    SDL_Renderer* ren;
public: 
    Script();
    ~Script();

    void loadObject(const json& mem);
    void loadHighlight(const json & mem);
    void init(const json& mem);
    void highlightLine(int k);
    void unHighlighLine(int k);

    void setRender(SDL_Renderer *& r);

    void render();
};

#endif
