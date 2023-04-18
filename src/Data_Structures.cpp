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
    Sketch::~Sketch();
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
    if(!mem.contains("name")) return ;
    if(mem["name"] == "StaticArray.json")
    {
        if(mem.contains("elements"))
        {
            for(int i = 0; i < mem["elements"].size() && i < capacity; i++)
            {
                elements[i]->setText(mem["elements"][i].get<std::string>());
            }
        }
    }
}

void Data_Structures::initStaticArray(const json &mem)
{
    type = 1;
    Sketch::setRender(ren);
    Sketch::init(mem);

    if(elements != nullptr)
    {
        delete [] elements;
        elements = nullptr;
    }

    capacity = 12;
    elements = new Sketch*[capacity];

    for(int i = 0; i < capacity; i++)
    {
        elements[i] = new Sketch;
        elements[i]->setRender(ren);
        if(mem.contains("element attributes"))
        {    
            elements[i]->init(mem["element attributes"]);
            
            int dx = mem["element attributes"]["dx"];
            int dy = mem["element attributes"]["dy"];

            elements[i]->addX(i * dx);
            elements[i]->addY(i * dy);
        }
    }
}

void Data_Structures::render()
{
    if(!isVisible()) return ;
    Sketch::render();
    for(int i = 0; i < capacity; i++)
        elements[i]->render();
}
