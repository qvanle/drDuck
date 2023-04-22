#include "SDL_timer.h"
#include "SYSTEM.hpp"
#include <Data_Structures.hpp>
#include <iterator>

int Data_Structures::size()
{
    return num;
}

Data_Structures::Data_Structures()
{
    finish = true;
    elements.clear();
    capacity = 0;
    ren = nullptr;
    num = 0;
    speed = 1;
}

Data_Structures::~Data_Structures()
{
    elements.clear();
    ren = nullptr;
    capacity = 0;
    num = 0;
    //Sketch::~Sketch();
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

    int ite = 0;
    num = 0;

    while(ite < (int)s.size() && num < capacity)
    {
        while(ite < (int)s.size() && s[ite] == ' ') ite++;
        std::string temp;
        while(ite < (int)s.size() && isdigit(s[ite]))
            temp += s[ite++];
        if(temp.empty()) temp = "0";
        elements[num++]->setText(temp);
        ite++;
    }

    for(int i = num; i < capacity; i++)
        elements[i]->setText("");

    for(int i = 0; i < capacity; i++)
    {
        elements[i]->show();
    }
}

void Data_Structures::StaticArrayInsert(int pos, int value, std::mutex & m)
{
    num++;
    for(int i = 0; i < num; i++) elements[i]->show();

    for(int i = num - 1; i > pos; i--)
    {


        m.lock();
        elements[i]->highight();
        elements[i - 1]->highight();
        m.unlock();

        while(getStep() == 0);
        decStep();

        SDL_Delay(400 / speed);

        m.lock();
        elements[i]->setText(elements[i - 1]->getText());
        m.unlock();
        SDL_Delay(500 / speed);

        while(getStep() == 0);

        m.lock();
        elements[i]->unHighlight();
        elements[i - 1]->unHighlight();
        m.unlock();
        SDL_Delay(100 / speed);
    }

    while(getStep() == 0);
    decStep();

    m.lock();
    elements[pos]->highight();
    m.unlock();

    SDL_Delay(500 / speed);

    m.lock();
    elements[pos]->setText(std::to_string(value));
    m.unlock();
    SDL_Delay(500 / speed);

    m.lock();
    elements[pos]->unHighlight();
    m.unlock();
    SDL_Delay(500 / speed);
}

void Data_Structures::create(std::string s)
{
    if(type == 1) StaticArrayCreate(s);
}

void Data_Structures::insert(std::string s1, std::string s2, std::mutex & m)
{
    if(num == capacity) return ;
    int pos = getFirstInt(s1);
    int value = getFirstInt(s2);
    pos = std::min(pos, num);
    step = -1;
    finish = false;
    if(type == 1) StaticArrayInsert(pos, value, m);
    finish = true;
}

void Data_Structures::StaticArrayUpdate(int pos, int value, std::mutex &m)
{
    for(int i = 0; i < num; i++) elements[i]->show();

    SDL_Delay(800 / speed);

    m.lock();
    elements[pos]->highight();
    m.unlock();
    while(getStep() == 0);
    decStep();

    SDL_Delay(400 / speed);

    m.lock();
    elements[pos]->setText(std::to_string(value));
    m.unlock();
    SDL_Delay(100 / speed);
    while(getStep() == 0);
    m.lock();
    elements[pos]->unHighlight();
    m.unlock();
}

void Data_Structures::StaticArrayErase(int pos, std::mutex &m)
{
    for(int i = 0; i < num; i++) elements[i]->show();
    
    num--;
    for(int i = pos; i < num; i++)
    {
        m.lock();
        elements[i]->highight();
        elements[i + 1]->highight();
        m.unlock();

        while(getStep() == 0);
        decStep();

        SDL_Delay(400 / speed);

        m.lock();
        elements[i]->setText(elements[i + 1]->getText());
        m.unlock();
        SDL_Delay(500 / speed);

        while(getStep() == 0);

        m.lock();
        elements[i]->unHighlight();
        elements[i + 1]->unHighlight();
        m.unlock();
        SDL_Delay(100 / speed);
    }
}
void Data_Structures::erase(std::string s1, std::mutex &m)
{
    if(num == 0) return ;
    int pos = getFirstInt(s1);
    pos = std::min(pos, num);
    step = -1;
    finish = false;
    if(type == 1) StaticArrayErase(pos, m);
    finish = true;
}

void Data_Structures::update(std::string s1, std::string s2, std::mutex &m)
{
    if(num == 0) return ;
    int pos = getFirstInt(s1);
    int value = getFirstInt(s2);
    step = -1;
    finish = false;
    pos = std::min(pos, num - 1);
    if(type == 1) StaticArrayUpdate(pos, value, m);
    finish = true;
}

void Data_Structures::speedUp()
{
    if(diff(speed, 3.0)) return ;
    speed += 0.25;
}

void Data_Structures::slowDown()
{
    if(diff(speed, 0.25)) return ;
    speed -= 0.25;
}

void Data_Structures::nextStep()
{
    stepMutex.lock();
    step = 1;
    stepMutex.unlock();
}

void Data_Structures::setStep(int k)
{
    stepMutex.lock();
    step = k;
    stepMutex.unlock();
}

void Data_Structures::decStep()
{
    stepMutex.lock();
    step--;
    stepMutex.unlock();
}

int Data_Structures::getStep()
{
    int val;
    stepMutex.lock();
    val = step;
    stepMutex.unlock();
    return val;
}


bool Data_Structures::isFinish()
{
    return finish;
}

