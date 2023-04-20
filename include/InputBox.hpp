#ifndef INPUTBOX 
#define INPUTBOX 

#include <Sketch.hpp>
#include <SYSTEM.hpp>
#include <Button.hpp>
#include <SDL2/SDL.h>


class InputBox: public Sketch
{
private:
    SDL_Renderer* ren;
    Sketch* boxTitle;
    std::vector<Sketch*> input;
    std::vector<Sketch*> texts;
    std::vector<Button*> buts;
    int focusOn;

    void setFocus(int k);
public:
    InputBox();
    ~InputBox();
    void setRender(SDL_Renderer *& r);
    void init(const json& mem);
    void typing(char ch);
    void pop();
    void render();
};

#endif 
