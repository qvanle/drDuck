#ifndef BUTTON
#define BUTTON

#include <Object.hpp>
#include <SYSTEM.hpp>

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL2/SDL_image.h>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Button : public Object
{
private:
    SDL_Renderer* ren;
    char* nextScreen;

public:
    Button();
    bool isChosen(int x, int y);
    void init(const char* name);
    void init(const char* dir, const char* name);
    void init(const json& mem);
    void setRenderer(SDL_Renderer* const& r);
    void render();
    void Delete();
    void clearTextures();
    char* const& getNextScreen();
    ~Button();
};
#endif
