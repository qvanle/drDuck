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
    Button ** buts;
    int ButNum;
    bool status;
    bool freeze;
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

    void moveTo(int x, int y, double time);
    void moveFrom(int x, int y, double time);

    ~Display();
};

#endif
