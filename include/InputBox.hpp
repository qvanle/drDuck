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
    void setInput(std::string s);
    void pop();
    void render();
    void mouseMove(int x, int y);
    void mousePress(int x, int y);
    Button* getButtonPressedByMouse(int x, int y);
    void nextFocus();
    std::string getText(int k);
};

#endif 
