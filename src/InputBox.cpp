#include "Sketch.hpp"
#include <InputBox.hpp>

InputBox::InputBox()
{
    ren = nullptr;
    boxTitle = nullptr;
    input.clear();
    texts.clear();
    buts.clear();
}

InputBox::~InputBox()
{
    ren = nullptr;
    if(boxTitle != nullptr)
    {
        delete boxTitle;
        boxTitle = nullptr;
    }
    input.clear();
    texts.clear();
    buts.clear();
}

void InputBox::setRender(SDL_Renderer *&r)
{
    ren = r;
}

void InputBox::init(const json &mem)
{
    Sketch::setRender(ren);
    Sketch::init(mem);
    if(mem.contains("title"))
    {
        boxTitle = new Sketch;
        boxTitle->setRender(ren);
        boxTitle->init(mem["title"]);
    }
    if(mem.contains("input"))
    {
        input.clear();
        input.resize(mem["input"].size());
        for(int i = 0; i < (int) input.size(); i++)
        {
            input[i] = new Sketch;
            input[i]->setRender(ren);
            input[i]->init(mem["input"][i]);
        }
    }
    if(mem.contains("texts"))
    {
        texts.clear();
        texts.resize(mem["texts"].size());
        for(int i = 0; i < (int) texts.size(); i++)
        {
            texts[i] = new Sketch;
            texts[i]->setRender(ren);
            texts[i]->init(mem["texts"][i]);
        }
    }
}

void InputBox::render()
{
    if(!isVisible()) return ;
    
    Sketch::render();

    if(boxTitle != nullptr)
    {
        boxTitle->render();
    }
    for(int i = 0; i < (int) input.size(); i++)
        input[i]->render();
    for(int i = 0; i < (int) texts.size(); i++)
        texts[i]->render();
    for(int i = 0; i < (int) buts.size(); i++)
        buts[i]->render();
}
