#include "Sketch.hpp"
#include <Script.hpp>

Script::Script()
{
    ren = nullptr;
}


Script::~Script()
{
    for(int i = 0; i < (int)texts.size(); i++)
        delete texts[i];
    texts.clear();
    ren = nullptr;
}

void Script::init(const json & mem)
{
    Sketch::setRender(ren);
    Sketch::init(mem);
    if(mem.contains("font")) Data["font"] = mem["font"];
    if(mem.contains("dy")) dy = mem["dy"];
}
void Script::loadTexts(std::string s)
{
    std::ifstream fin(s);
    
    while(!fin.eof())
    {
        std::string temp;
        std::getline(fin, temp);
        texts.push_back(nullptr);
        texts.back() = new Sketch;
        texts.back()->init(Data);
        texts.back()->addY(dy * (texts.size() - 1));
    }

    fin.close();
}

void Script::highlightLine(int k)
{
    texts[k]->highlight();
}

void Script::setRender(SDL_Renderer *& r)
{
    ren = r;
}

void Script::render()
{
    if(!isVisible()) return ;
    Sketch::render();
    for(int i = 0; i < texts.size(); i++)
        texts[i]->render();
}
