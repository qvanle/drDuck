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
public:
    bool isFocus();
    bool changeFocus(int x, int y);
    Display();
    void init(const char* dir, const char* name);
    void init(const json& mem);
    void loadButtons(const json& mem);
    void loadButton(Button *& but, const json& mem);
    void setRenderer(SDL_Renderer* const&  ren);
    void render();
    void mouseMove(int x, int y);
    void mousePressedButton(int x, int y, char*& MSG);
    void DeleteButs();

    void moveTo(int x, int y, double time);
    void moveFrom(int x, int y, double time);

    ~Display();
};

#endif
