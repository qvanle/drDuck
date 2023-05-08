#ifndef INPUTBOX 
#define INPUTBOX 

#include <Sketch.hpp>
#include <SYSTEM.hpp>
#include <Button.hpp>
#include <SDL2/SDL.h>

/**
 * @brief class that create an input box and render it to the screen
 * Popup a box that can typing in.
*/

class InputBox: public Sketch
{
private:
    SDL_Renderer* ren;
    Sketch* boxTitle;
    vector<Sketch*> input;
    vector<Sketch*> texts;
    vector<Button*> buts;
    int focusOn;

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
    void setFocus(int k);
    std::string getText(int k);
};

#endif 
