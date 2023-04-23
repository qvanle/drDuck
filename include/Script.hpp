#ifndef PSEUDOCODE 
#define PSEUDOCODE

#include <SYSTEM.hpp>
#include <Sketch.hpp>
#include <SDL2/SDL.h>


class Script : public Sketch
{
private:
    std::vector<Sketch*> texts;
    json Data;
    int dx, dy;
    SDL_Renderer* ren;
public: 
    Script();
    ~Script();

    void loadTexts(std::string s);
    void init(const json& mem);
    void highlightLine(int k);
    void unHighlighLine(int k);

    void setRender(SDL_Renderer *& r);

    void render();
};

#endif
