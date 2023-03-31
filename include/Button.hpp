#ifndef BUTTON
#define BUTTON

#include <SYSTEM.hpp>

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL2/SDL_image.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Button 
{
private:
    SDL_Texture** grains;
    SDL_Renderer* renderer;
    int SizeOfGrains;
    int status;
    bool visible;
    SDL_Rect coor;
    char* nextScreen;

public:
    Button();
    void show();
    void hide();
    void nxStatus();
    void pvStatus();
    bool isChosen(int x, int y);
    bool isPressed(int x, int y);
    void setTextures(const json& mem);
    void init(const char* name);
    void init(const char* dir, const char* name);
    void init(const json& mem);
    void setRenderer(SDL_Renderer* const& ren);
    void render();
    int size();
    void Delete();
    void clearTextures();
    char* const& getNextScreen();
    ~Button();
};
#endif
