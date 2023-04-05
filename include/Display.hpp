#ifndef DISPLAY
#define DISPLAY

#include <SDL2/SDL.h>
#include <SDL_surface.h>
#include <SDL_render.h>
#include <SDL2/SDL_image.h>

#include <nlohmann/json.hpp>

#include <SYSTEM.hpp>
#include <Button.hpp>


using json = nlohmann::json;

class Display
{
private:
    SDL_Texture* background;
    SDL_Renderer * renderer;
    SDL_Rect coor;
    Button ** buts;
    int ButNum;
    bool status;
public:
    bool isFocus();
    bool changeFocus(int x, int y);
    Display();
    void init(const char* dir, const char* name);
    void loadBackground(const json& mem);
    void loadButton(Button *& but, const json& mem);
    void setRenderer(SDL_Renderer* const&  ren);
    void render();
    void mouseMove(int x, int y);
    void mousePressedButton(int x, int y, char*& MSG);
    void DeleteButs();
    ~Display();
};

#endif
