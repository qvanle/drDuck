#ifndef WINDOW
#define WINDOW

#include <SDL_render.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <Display.hpp>
#include <Data_Structures.hpp>
#include <SYSTEM.hpp>
#include <InputBox.hpp>


class MyWindow
{
    private:
        int status;
        int WIDTH;
        int HEIGHT;
        int FocusOn;
        int fps;

        Data_Structures* DT;
        std::string type;
        InputBox* input;

        SDL_Window* window;
        SDL_Renderer* renderer;
        std::vector<Display*> screen;
        void shutdown();
        void deleteScreen();

        SDL_Event event;
        std::mutex UImutex;
        std::mutex soundMutex;

        bool isChangeScreen(Button *& but);
        bool isChangeScreen(Button *& but, const json &mem);
        bool isDToperator(Button *& but);
        bool isInputButton(Button *& but);
        bool isPlayButton(Button *& but);

        SDL_AudioSpec audioSpec;
        Uint32 waveLength;
        Uint8 *waveBuffer;
        bool soundOn;
        bool turnOn;

    public:
            MyWindow();
            void loadScreen(Display *& screen, const json& mem);
            void init();
            void action();
            void process();
            void speak();
            void render();
            bool isOpen();
            bool isClose();
            bool isHanging();

            void changeScreens(const char* const &name);
            Display *& top();

            void mouseMove(int x, int y);
            void mousePress(int x, int y);
            void typing(SDL_Keysym key);
            void run();

            ~MyWindow();
};

#endif
