#include "SDL_error.h"
#include "Sketch.hpp"
#include <Data_Structures.hpp>

Data_Structures::Data_Structures()
{
    elements = nullptr;
    capacity = 0;
    ren = nullptr;
    num = 0;
}

Data_Structures::~Data_Structures()
{
    if(elements != nullptr)
    {
        delete [] elements;
        elements = nullptr;
    }
    ren = nullptr;
    capacity = 0;
    num = 0;
}

void Data_Structures::init(const json & mem)
{
    if(!mem.contains("name")) return ;
    if(mem["name"].get<std::string>() == "StaticArray.json")
    {
        initStaticArray(mem);
    }
}

void Data_Structures::setRender(SDL_Renderer *&r)
{
    ren = r;
}

void Data_Structures::loadValue(const json &mem)
{
    for(int i = 0; i < mem.size(); i++)
    {
        elements[i]->setText(mem[i].get<std::string>());
    }
}

void Data_Structures::initStaticArray(const json &mem)
{
    Sketch::setRender(ren);
    Sketch::init(mem);

    capacity = 12;
    elements = new Sketch*[capacity];
    for(int i = 0; i < capacity; i++)
    {
        elements[i] = new Sketch;
        elements[i]->setRender(ren);
        if(mem.contains("elements attributes"))
        {    
            elements[i]->init(mem["elements attributes"]);
            
            int dx = mem["elements attributes"]["dx"];
            int dy = mem["elements attributes"]["dy"];

            elements[i]->addX(i * dx);
            elements[i]->addY(i * dy);
        }   
    }
}

void Data_Structures::render()
{
    Sketch::render();
    for(int i = 0; i < capacity; i++)
        elements[i]->render();
}
