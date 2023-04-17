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
    if(mem["name"] == "StaticArray.json")
    {
        initStaticArray(mem);
    }
}

void Data_Structures::setRender(SDL_Renderer *&r)
{
    ren = r;
}

void Data_Structures::initStaticArray(const json &mem)
{
    Object::init(mem, ren);
}
