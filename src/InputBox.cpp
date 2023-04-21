#include "Button.hpp"
#include "SYSTEM.hpp"
#include <InputBox.hpp>

InputBox::InputBox()
{
    ren = nullptr;
    boxTitle = nullptr;
    input.clear();
    texts.clear();
    buts.clear();
    focusOn = -1;
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
    focusOn = -1;
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
    if(mem.contains("buttons"))
    {
        buts.clear();
        buts.resize(mem["buttons"].size());
        for(int i = 0; i < (int) buts.size(); i++)
        {
            buts[i] = new Button;
            buts[i]->setRenderer(ren);
            buts[i]->init(
                    GLOBAL::AtrbButtons,
                    mem["buttons"][i]["name"].get<std::string>().c_str()
                    );
            buts[i]->init(mem["buttons"][i]);
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

void InputBox::setFocus(int k)
{
    if(!isVisible()) return ;
    focusOn = k;
}
void InputBox::typing(char ch)
{
    if(focusOn == -1) return ;
    input[focusOn]->addChar(ch);
}

void InputBox::setInput(std::string s)
{
    if(focusOn == 1) return ;
    input[focusOn]->setText(s);
}

void InputBox::pop()
{
    if(!isVisible()) return ;
    if(focusOn == -1) return ;
    input[focusOn]->popChar();
}

void InputBox::mouseMove(int x, int y)
{
    if(!isVisible()) return ;

    for(int i = 0; i < (int) buts.size(); i++)
        if(buts[i]->isChosen(x, y)) break;

    for(int i = 0; i < (int) input.size(); i++)
        if(input[i]->isLieInside(x, y))
            setFocus(i);
}

void InputBox::mousePress(int x, int y)
{
    if(!isVisible()) return ;
    for(int i = 0; i < (int) input.size(); i++)
    {
        setFocus(i);
        return ;
    }
}

void InputBox::nextFocus()
{
    if(!isVisible()) return ;
    if(focusOn == -1) 
    {
        if(!input.empty()) focusOn = 0;
        return ;
    }
    if(input.empty()) return ;
    focusOn = (focusOn + 1) % input.size();
}

Button* InputBox::getButtonPressedByMouse(int x, int y)
{
    if(!isVisible()) return nullptr;

    for(int i = 0; i < (int) buts.size(); i++)
        if(buts[i]->isChosen(x, y))
            return buts[i];
    return nullptr;
}


std::string InputBox::getText(int k)
{
    return input[k]->getText();
}
