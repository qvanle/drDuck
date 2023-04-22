#ifndef DISPLAY
#define DISPLAY

#include <SDL2/SDL.h>
#include <SDL_surface.h>
#include <SDL_render.h>
#include <SDL2/SDL_image.h>

#include <SYSTEM.hpp>
#include <Button.hpp>
#include <Object.hpp>



class Display : public Object
{
private:
    SDL_Renderer * ren;
    std::vector<Button*> buts;
    bool status;
    int appear;
public:
    bool isFreezed();
    bool isFocus();
    bool changeFocus(int x, int y);
    Display();
    void init(const char* dir, const char* name);
    void init(const json& mem);
    void loadButtons(const json& mem);
    void loadButton(Button *& but, const json& mem);
    void setRenderer(SDL_Renderer* const&  ren);
    void trigger(int x, int y);
    void render();
    void render(bool update);
    void mouseMove(int x, int y);
    Button* mousePressedButton(int x, int y);
    void DeleteButs();
    void hideButton(int k);
    void showButton(int k);

    void moveTo(int x, int y, double time);
    void appearFromBot(double time);
    void appearFromRight(double time);
    void disappearToBot(double time);
    void disappearToRight(double time);
    int getAppear();

    ~Display();
};

#endif
