#include "SDL_pixels.h"
#include "SDL_timer.h"
#include "SYSTEM.hpp"
#include "Sketch.hpp"
#include <Data_Structures.hpp>
#include <iterator>
#include <string>

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
    std::string name = mem["name"].get<std::string>();
    if(name == "StaticArray.json")
    {
        initStaticArray(mem);
    }else if(name == "DynamicArray.json")
    {
        initDynamicArray(mem);
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
    elements.resize(capacity);

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
        }
    }
}

void Data_Structures::initDynamicArray(const json & mem)
{
    type = 2;
    Sketch::setRender(ren);
    Sketch::init(mem);

    capacity = 12;
    elements.clear();
    elements.resize(capacity * 2);

    for(int i = 0; i < capacity; i++)
    {
        elements[i] = new Sketch;
        elements[i]->setRender(ren);

        elements[i + capacity] = new Sketch;
        elements[i + capacity]->setRender(ren); 

        if(mem.contains("element attributes"))
        {    
            elements[i]->init(mem["element attributes"]);
            elements[i + capacity]->init(mem["element attributes"]);
            int dx = mem["element attributes"]["dx"];
            int dy = mem["element attributes"]["dy"];

            elements[i]->addX(i * dx);

            elements[i + capacity]->addX(i * dx);
            elements[i + capacity]->addY(dy);
        }
    }

}

void Data_Structures::render()
{
    if(!isVisible()) return ;
    Sketch::render();
    for(int i = 0; i < elements.size(); i++)
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

void Data_Structures::DynamicArrayCreate(std::string s)
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

    for(int i = 0; i < num; i++)
    {
        elements[i]->show();
    }

    std::cerr << num << "\n";
}

void Data_Structures::DynamicArrayInsert(int pos, int value, std::mutex & m)
{
    m.lock();
    for(int i = 0; i < num + 1; i++)
        elements[i + capacity]->setText("");
    m.unlock();


    while(getStep() == 0);
    decStep();

    SDL_Delay(400 / speed);

    for(int i = 0; i < num + 1; i++)
        elements[i + capacity]->show();

    bool inserted = false;

    for(int i = 0; i < num; i++)
    {
        if(i == pos)
        {
            m.lock();
            elements[i + capacity]->highight();
            m.unlock();

            SDL_Delay(400 / speed);

            while(getStep() == 0);
            decStep();


            m.lock();
            elements[i + capacity]->setText(std::to_string(value));
            m.unlock();

            SDL_Delay(500 / speed);
            while(getStep() == 0);
            decStep();

            m.lock();
            elements[i + capacity]->unHighlight();
            m.unlock();
            inserted = true;
            SDL_Delay(200 / speed);

        }

        m.lock();
        elements[i]->highight();
        elements[i + capacity + inserted]->highight();
        m.unlock();


        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        elements[i + capacity + inserted]->setText(elements[i]->getText());
        m.unlock();
        SDL_Delay(500 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        elements[i]->unHighlight();
        elements[i + capacity + inserted]->unHighlight();
        m.unlock();
    }
    int i = num;
    if(i == pos)
    {
        m.lock();
        elements[i + capacity]->highight();
        m.unlock();

        SDL_Delay(400 / speed);

        while(getStep() == 0);
        decStep();


        m.lock();
        elements[i + capacity]->setText(std::to_string(value));
        m.unlock();

        SDL_Delay(500 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        elements[i + capacity]->unHighlight();
        m.unlock();
        inserted = true;
        SDL_Delay(200 / speed);

    }
    while(getStep() == 0);
    decStep();

    SDL_Delay(200 / speed);

    m.lock();
    num++;
    for(int i = 0; i < num; i++)
    {
        elements[i]->setText(elements[i + capacity]->getText());
        elements[i]->show();
        elements[i + capacity]->hide();
    }
    m.unlock();
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
    else if(type == 2) DynamicArrayCreate(s);
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
    else if(type == 2) DynamicArrayInsert(pos, value, m);
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

void Data_Structures::StaticArraySearch(int value, std::mutex &m)
{
    for(int i = 0; i < num; i++) elements[i]->show();

    for(int i = 0; i < num; i++)
    {
        m.lock();
        elements[i]->highight();
        m.unlock();

        SDL_Delay(400 / speed);

        while(getStep() == 0);
        decStep();

        m.lock();
        bool valid = std::to_string(value) == elements[i]->getText();
        if(valid)
            elements[i]->FillWithColor(SDL_Color({10, 155, 10, 255}));
        else 
            elements[i]->FillWithColor(SDL_Color({155, 10, 10, 255}));
        m.unlock();

        SDL_Delay(600 / speed);

        m.lock();
        elements[i]->FillWithColor();
        m.unlock();

        SDL_Delay(400 / speed);

        m.lock();
        elements[i]->unHighlight();
        m.unlock();
        SDL_Delay(100 / speed);
        if(valid) break;
    }
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

void Data_Structures::search(std::string s2, std::mutex &m)
{
    if(num == 0) return ;
    int value = getFirstInt(s2);
    step = -1;
    finish = false;
    if(type == 1) StaticArraySearch(value, m);
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

