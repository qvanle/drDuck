#include <Script.hpp>

Script::Script()
{
    obj = nullptr;
    ren = nullptr;
}


Script::~Script()
{
    for(int i = 0; i < (int)lines.size(); i++)
        delete lines[i];
    lines.clear();
    if(obj != nullptr) delete obj;
    obj = nullptr;
    ren = nullptr;
}

void Script::loadObject(const json &mem)
{
    if(obj != nullptr) delete obj;

    obj = new Object;
    obj->init(mem, ren);
}

void Script::loadHighlight(const json &mem)
{
    lines.clear();
    lines.resize(mem["size"]);
    int dx = mem["dx"];
    int dy = mem["dy"];

    for(int i = 0; i < (int) lines.size(); i++)
    {
        lines[i] = new Sketch;
        lines[i]->setRender(ren);
        lines[i]->init(mem);
        lines[i]->addX(dx * i);
        lines[i]->addY(dy * i);
    }
}
void Script::init(const json & mem)
{
    Sketch::setRender(ren);
    Sketch::init(mem);
    if(mem.contains("object"))
    {
        loadObject(mem["object"]);
    }
    if(mem.contains("highlight"))
    {
        loadHighlight(mem["highlight"]);
    }
}

void Script::highlightLine(int k)
{
    lines[k]->show();
}
void Script::unHighlighLine(int k)
{
    lines[k]->hide();
}

void Script::setRender(SDL_Renderer *& r)
{
    ren = r;
}

void Script::render()
{
    if(!isVisible()) return ;
    Sketch::render();
    if(obj != nullptr) obj->render(false);
    for(int i = 0; i < lines.size(); i++)
        lines[i]->render();
}
