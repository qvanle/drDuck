#include <Data_Structures.hpp>

Data_Structures::Data_Structures()
{
    elements.clear();
    capacity = 0;
    ren = nullptr;
    num = 0;
}

Data_Structures::~Data_Structures()
{
    elements.clear();
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

    elements.clear();

    capacity = 12;
    elements.resize(12);

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

bool isdigit(char ch)
{
    return '0' <= ch && ch <= '9';
}


void Data_Structures::StaticArrayCreate(std::string s)
{
    int *arr;
    int n = 0;
    
    show();
    for(int i = 0; i < capacity; i++)
    {
        elements[i]->show();
    }

    int ite = 0;
    num = 0;

    while(ite < (int)s.size())
    {
        while(ite < (int)s.size() && s[ite] == ' ') ite++;
        std::string temp;
        while(ite < (int)s.size() && isdigit(s[ite]))
            temp += s[ite++];
        if(temp.empty()) temp = "0";
        elements[num++]->setText(temp);
        ite++;
    }
}

void Data_Structures::StaticArrayInsert(int pos, int value)
{

}

void Data_Structures::create(std::string s)
{
    if(type == 1) StaticArrayCreate(s);
}

void Data_Structures::insert(int pos, int value)
{
    if(type == 1) StaticArrayInsert(pos, value);
}
