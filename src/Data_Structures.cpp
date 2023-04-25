#include "SDL_assert.h"
#include "SDL_scancode.h"
#include "SDL_timer.h"
#include "SYSTEM.hpp"
#include <Data_Structures.hpp>
#include <memory>

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
    script = nullptr;
    arrowE = nullptr;
    depth = 3;
    lineDepth = 0;
    circle = false;
}

Data_Structures::~Data_Structures()
{
    elements.clear();
    ren = nullptr;
    capacity = 0;
    num = 0;
    if(script != nullptr) delete script;
    script = nullptr;
    if(arrowE != nullptr) delete arrowE;
    arrowE = nullptr;
    //Sketch::~Sketch();
}

void Data_Structures::init(const json & mem)
{
    if(!mem.contains("name")) return ;
    std::string name = mem["name"].get<std::string>();
    if(mem.contains("script"))
    {
        if(script != nullptr) delete script;
        script = new Script;
        script->setRender(ren);
        script->init(mem["script"]);
    }
    if(name == "StaticArray.json")
    {
        initStaticArray(mem);
    }else if(name == "DynamicArray.json")
    {
        initDynamicArray(mem);
    }else if(name == "SinglyLinkedList.json")
    {
        initSinglyLinkedList(mem);
    }else if(name == "DoublyLinkedList.json")
    {
        initDoublyLinkedList(mem);
    }else if(name == "CircularLinkedList.json")
    {
        initCircularLinkedList(mem);
    }
}

void Data_Structures::setRender(SDL_Renderer *&r)
{
    ren = r;
}

void Data_Structures::loadValue(const json &mem)
{
    if(!mem.contains("name")) return ;
    if(mem.contains("elements"))
    {
        for(int i = 0; i < mem["elements"].size() && i < capacity; i++)
        {
            elements[i]->setText(mem["elements"][i].get<std::string>());
            if(mem.contains("visible") && mem["visible"])
                elements[i]->show();
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

void Data_Structures::connect(int i, int j)
{
    if(i == -1 || j == -1) return ;
    if(i == j) return ;
    if(i + 1 == j && j != capacity)
    {
        lineRight(i, 2);
    }else if(i - 1 == j)
    {
        lineLeft(i, 2);
    }else if (i < capacity && j < capacity) 
        Circling(i, j, 2);
    else if(i - capacity == j) lineUp(i, 7);
    else if(j - capacity == i) lineDown(i, 7);
    else if(i > capacity && j < capacity) connect(i, j + capacity), connect(j + capacity, j);
    else if(i < capacity && j > capacity) connect(i, i + capacity), connect(i + capacity, j);
}

void Data_Structures::Circling(int i, int j, int k)
{
    int temp = depth;
    depth = k;
    Circling(i, j);
    depth = temp;
}

void Data_Structures::lineLeft(int i, int len)
{
    arrowW->setX(elements[i]->getCoor().x + arrowW->getCoor().w);
    arrowW->setY(elements[i]->getCoor().y);


    while(len--)
    {
        arrowW->addX(-arrowW->getCoor().w);
        arrowW->render(false);
    }
}

void Data_Structures::lineUp(int i, int len)
{
    arrowN->setX(elements[i]->getCoor().x);
    arrowN->setY(elements[i]->getCoor().y);
    while(len--)
    {
        arrowN->addY(-arrowN->getCoor().h);
        arrowN->render(false);
    }
}

void Data_Structures::lineRight(int i, int len)
{
    if(len == 0) return ;

    arrowE->setX(elements[i]->getCoor().x - arrowE->getCoor().w + elements[i]->getCoor().w);;
    arrowE->setY(elements[i]->getCoor().y);
    arrowE->render(false);

    while(--len)
    {
        arrowE->addX(arrowE->getCoor().w);
        arrowE->render(false);
    }
}

void Data_Structures::lineDown(int i, int len)
{
    if(len == 0) return ;
    arrowS->setX(elements[i]->getCoor().x);
    arrowS->setY(elements[i]->getCoor().y + elements[i]->getCoor().h);
    arrowS->render(false);

    while(--len)
    {
        arrowS->addY(arrowS->getCoor().h);
        arrowS->render(false);
    }
}

void Data_Structures::Circling(int i, int j)
{
    if(i >= num || j >= num || i == j) return ;

    if(i < j)
    {
        arrowN->setX(elements[i]->getCoor().x);
        arrowN->setY(elements[i]->getCoor().y - arrowN->getCoor().h);
        arrowN->render(false);
        for(int k = 1; k < depth; k++)
        {
            arrowN->addY(-arrowN->getCoor().h);
            arrowN->render(false);
        }

        arrowS->setY(arrowN->getCoor().y);
        arrowS->setX(elements[j]->getCoor().x);
        arrowS->render(false);

        for(int k = 1; k < depth; k++)
        {
            arrowS->addY(arrowS->getCoor().h);
            arrowS->render(false);
        }

        arrowE->setX(arrowN->getCoor().x + arrowN->getCoor().w / 2);
        arrowE->setY(arrowN->getCoor().y - arrowN->getCoor().h - 8);

        do 
        {
            arrowE->render(false);
            arrowE->addX(arrowE->getCoor().w);
        }while(arrowE->getCoor().x - arrowE->getCoor().w < arrowS->getCoor().x);
        return ;
    }

    std::swap(i, j);

    arrowS->setX(elements[i]->getCoor().x);
    arrowS->setY(elements[i]->getCoor().y - arrowN->getCoor().h);
    arrowS->render(false);
    for(int k = 1; k < depth; k++)
    {
        arrowS->addY(-arrowS->getCoor().h);
        arrowS->render(false);
    }

    arrowN->setY(arrowS->getCoor().y);
    arrowN->setX(elements[j]->getCoor().x);
    arrowN->render(false);

    for(int k = 1; k < depth; k++)
    {
        arrowN->addY(arrowN->getCoor().h);
        arrowN->render(false);
    }

    arrowW->setX(arrowS->getCoor().x + arrowS->getCoor().w / 2);
    arrowW->setY(arrowS->getCoor().y - arrowS->getCoor().h - 8);

    do 
    {
        arrowW->render(false);
        arrowW->addX(arrowW->getCoor().w);
    }while(arrowW->getCoor().x - arrowW->getCoor().w < arrowN->getCoor().x);
}

void Data_Structures::Lining()
{
    if(arrowE == nullptr) return ;

    for(int i = 0; i + 1 < num; i++)
    {
        arrowE->setX(elements[i]->getCoor().x + elements[i]->getCoor().w);
        arrowE->setY(elements[i]->getCoor().y);
        arrowE->render(false);
    }
}

void Data_Structures::render()
{
    if(!isVisible()) return ;
    Sketch::render();
    for(int i = 0; i < num; i++)
        elements[i]->show();
    for(int i = 0; i < connection.size(); i++)
    {
        if(elements[i]->isVisible() && connection[i] != -1 && elements[connection[i]]->isVisible())
            connect(i, connection[i]);
    }
    for(int i = 0; i < elements.size(); i++)
    {
        elements[i]->render();
    }
    if(script != nullptr)
    {
        script->render();
    }
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
}

void Data_Structures::DynamicArrayInsert(int pos, int value, std::mutex & m)
{
    m.lock();
    for(int i = 0; i < num + 1; i++)
        elements[i + capacity]->setText("");

    json mem;
    readJson(GLOBAL::AtrbScript + "DynamicArrayInsert.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(0);
    m.unlock();

    SDL_Delay(800 / speed);

    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(0);
    script->highlightLine(1);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(1);
    script->highlightLine(3);
    m.unlock();

    for(int i = 0; i < num + 1; i++)
        elements[i + capacity]->show();

    bool inserted = false;

    for(int i = 0; i < num; i++)
    {
        if(i == pos)
        {
            m.lock();
            elements[i + capacity]->highlight();
            script->highlightLine(5);
            script->highlightLine(6);
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
            script->unHighlighLine(5);
            script->unHighlighLine(6);
            m.unlock();
            inserted = true;
            SDL_Delay(200 / speed);

        }

        m.lock();
        script->highlightLine(8);
        elements[i]->highlight();
        elements[i + capacity + inserted]->highlight();
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
        script->unHighlighLine(8);
        m.unlock();
    }
    int i = num;
    if(i == pos)
    {
        m.lock();
        script->highlightLine(9);
        script->highlightLine(10);
        elements[i + capacity]->highlight();
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
        script->unHighlighLine(9);
        script->unHighlighLine(10);
        elements[i + capacity]->unHighlight();
        m.unlock();
        inserted = true;
        SDL_Delay(200 / speed);

    }
    while(getStep() == 0);
    decStep();
    m.lock();
    script->highlightLine(11);
    script->highlightLine(13);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(11);
    script->unHighlighLine(13);
    script->highlightLine(14);
    num++;
    for(int i = 0; i < num; i++)
    {
        elements[i]->setText(elements[i + capacity]->getText());
        elements[i]->show();
        elements[i + capacity]->hide();
    }
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();
    m.lock();
    script->unHighlighLine(14);
    m.unlock();
}

void Data_Structures::SinglyLinkedListErase(int pos, std::mutex & m)
{
    m.lock();
    for(int i = 0; i < num; i++)
        elements[i]->show();

    json mem;
    readJson(GLOBAL::AtrbScript + "SinglyLinkedListDelete.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();

    script->highlightLine(0);
    m.unlock();

    pos = std::min(pos, num - 1);

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(0);
    m.unlock();
    if(pos == 0) 
    {
        m.lock();
        elements[0]->FillWithColor({155, 10, 10, 255});
        script->highlightLine(2);
        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        script->unHighlighLine(2);
        connection[pos] = -1;
        script->highlightLine(3);
        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        script->unHighlighLine(3);
        script->highlightLine(4);
        elements[0]->FillWithColor({10, 155, 10, 255});
        for(int i = pos; i + 1 < num; i++)
        {
            elements[i]->setText(elements[i + 1]->getText());
            connection[i] = i + 1;
        }
        num--;
        elements[num]->hide();
        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        elements[0]->FillWithColor();
        script->unHighlighLine(4);
        m.unlock();
        return ;
    }
    m.lock();
    script->highlightLine(6);
    m.unlock();

    for(int i = 0; i < pos; i++)
    {
        m.lock();
        script->highlightLine(7);
        script->highlightLine(8);
        elements[i]->highlight();
        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        script->unHighlighLine(7);
        script->unHighlighLine(8);
        elements[i]->unHighlight();
        m.unlock();
        SDL_Delay(200 / speed);

    }

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();


    m.lock();
    elements[pos]->FillWithColor(SDL_Color({155, 10, 10, 255}));
    script->unHighlighLine(6);
    script->highlightLine(9);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(9);
    script->highlightLine(10);
    elements[pos]->FillWithColor();
    connection[pos - 1] = pos + 1 != num ? pos + 1 : -1;
    connection[pos] = -1;
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();


    m.lock();
    script->unHighlighLine(10);
    script->highlightLine(11);
    if(pos != 0) connection[pos - 1] = pos;
    for(int i = pos; i + 1 < num; i++)
    {
        elements[i]->setText(elements[i + 1]->getText());
        connection[i] = i + 1;
    }
    num--;
    elements[num]->hide();
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(11);
    m.unlock();
}

void Data_Structures::SinglyLinkedListSearch(int value, std::mutex & m)
{
    m.lock();
    for(int i = 0; i < num; i++)
        elements[i]->show();
    m.unlock();

    for(int i = 0; i < num; i++)
    {
        m.lock();
        elements[i]->highlight();
        m.unlock();

        SDL_Delay(400 / speed);

        while(getStep() == 0);
        decStep();

        m.lock();
        bool valid = std::to_string(value) == elements[i]->getText();
        if(valid)
        {
            elements[i]->FillWithColor(SDL_Color({10, 155, 10, 255}));
        }else
        {
            elements[i]->FillWithColor(SDL_Color({155, 10, 10, 255}));
        }
        m.unlock();

        SDL_Delay(400 / speed);

        m.lock();
        elements[i]->FillWithColor();
        m.unlock();

        SDL_Delay(400 / speed);

        m.lock();
        elements[i]->unHighlight();
        m.unlock();
        SDL_Delay(200 / speed);
        if(valid) 
        {
            break;
        }
    }
}

void Data_Structures::SinglyLinkedListInsert(int pos, int value, std::mutex & m)
{
    if(num == capacity) return ;
    m.lock();

    json mem;
    readJson(GLOBAL::AtrbScript + "SinglyLinkedListInsert.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(0);

    for(int i = 0; i < num; i++)
        elements[i]->show();
    elements[pos + capacity]->show();
    elements[pos + capacity]->setText(std::to_string(value));
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(0);
    m.unlock();


    if(pos == 0)
    {
        m.lock();
        script->highlightLine(2);
        script->highlightLine(3);
        script->highlightLine(4);
        connection[capacity] = 0;
        m.unlock();


        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();


        m.lock();

        script->unHighlighLine(2);
        script->unHighlighLine(3);
        script->unHighlighLine(4);

        connection[capacity] = -1;

        for(int i = num; i > 0; i--)
            elements[i]->setText(elements[i - 1]->getText());

        elements[0]->setText(std::to_string(value));
        elements[num]->show();
        elements[capacity]->hide();
        connection[num - 1] = num;

        num++;

        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        return ;
    }
    m.lock();
    script->highlightLine(6);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();


    for(int i = 0; i < pos && i < num; i++)
    {
        m.lock();
        elements[i]->highlight();
        script->highlightLine(7);
        script->highlightLine(8);
        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        elements[i]->unHighlight();
        script->unHighlighLine(7);
        script->unHighlighLine(8);
        m.unlock();
        SDL_Delay(100 / speed);
    }

    m.lock();
    script->unHighlighLine(6);
    elements[pos - 1]->FillWithColor({10, 155, 10, 255});
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    if(pos >= num)
    {
        m.lock();
        script->highlightLine(9);
        connection[num - 1] = num + capacity;
        m.unlock();

        SDL_Delay(800 / speed);

        m.lock();
        connection[num - 1] = num;
        elements[pos + capacity]->hide();
        connection[num] = -1;
        connection[pos + capacity] = -1;
        elements[num]->setText(std::to_string(value));
        elements[num]->show();
        num++;
        script->unHighlighLine(9);
        elements[pos - 1]->FillWithColor();
        m.unlock();

        return ;
    }


    m.lock();
    script->highlightLine(9);
    connection[pos + capacity] = pos;
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    connection[pos - 1] = pos + capacity;
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(9);
    elements[pos - 1]->FillWithColor();
    connection[pos - 1] = pos;
    connection[pos + capacity] = -1;

    for(int i = num + 1; i > pos; i--)
        elements[i]->setText(elements[i - 1]->getText());
    elements[pos]->setText(std::to_string(value));
    elements[pos + capacity]->hide();
    connection[num - 1] = num;
    num++;
    m.unlock();
}

void Data_Structures::StaticArrayInsert(int pos, int value, std::mutex & m)
{

    m.lock();
    num++;
    for(int i = 0; i < num; i++) elements[i]->show();
    json mem;
    readJson(GLOBAL::AtrbScript + "StaticArrayInsert.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(4);
    m.unlock();

    SDL_Delay(800 / speed);
    m.lock();
    script->unHighlighLine(4);
    script->highlightLine(8);
    script->highlightLine(9);
    m.unlock();
    for(int i = num - 1; i > pos; i--)
    {
        m.lock();
        elements[i]->highlight();
        elements[i - 1]->highlight();
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
    script->unHighlighLine(8);
    script->unHighlighLine(9);
    script->highlightLine(11);
    script->highlightLine(13);
    elements[pos]->highlight();
    m.unlock();

    SDL_Delay(500 / speed);

    m.lock();
    elements[pos]->setText(std::to_string(value));
    m.unlock();
    SDL_Delay(500 / speed);

    m.lock();
    elements[pos]->unHighlight();
    script->unHighlighLine(11);
    script->unHighlighLine(13);
    m.unlock();
    SDL_Delay(500 / speed);

    m.lock();
    script->highlightLine(15);
    m.unlock();

    SDL_Delay(800 / speed);

    m.lock();
    script->unHighlighLine(15);
    m.unlock();

}

void Data_Structures::SinglyLinkedListCreate(std::string s)
{

    connection.clear();
    connection.resize(capacity * 2, -1);
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

    for(int i = num; i < 2 * capacity; i++)
    {
        elements[i]->hide();
        elements[i]->setText("");
    }
    for(int i = 0; i < num; i++)
    {
        elements[i]->show();
        connection[i] = (i + 1 == num) ? -1 : i + 1;
    }
}


void Data_Structures::create(std::string s)
{
    if(script != nullptr) script->hide();
    if(type == 1) StaticArrayCreate(s);
    else if(type == 2) DynamicArrayCreate(s);
    else if(type == 3) SinglyLinkedListCreate(s);
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
    else if(type == 3) SinglyLinkedListInsert(pos, value, m);
    finish = true;
}

void Data_Structures::DynamicArrayUpdate(int pos, int value, std::mutex &m)
{

    m.lock();

    for(int i = 0; i < num; i++) elements[i]->show();
    elements[pos]->highlight();

    json mem;
    readJson(GLOBAL::AtrbScript + "DynamicArrayUpdate.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(0);
    m.unlock();


    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();


    m.lock();
    script->unHighlighLine(0);
    script->highlightLine(1);
    elements[pos]->setText(std::to_string(value));
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    elements[pos]->unHighlight();
    script->unHighlighLine(1);
    script->highlightLine(2);
    m.unlock();


    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(2);
    m.unlock();
}

void Data_Structures::StaticArraySearch(int value, std::mutex &m)
{
    m.lock();
    for(int i = 0; i < num; i++) elements[i]->show();
    json mem;
    readJson(GLOBAL::AtrbScript + "StaticArraySearch.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->highlightLine(3);
    script->show();

    m.unlock();
    SDL_Delay(800 / speed);

    m.lock();
    script->unHighlighLine(3); 
    script->highlightLine(5);
    script->highlightLine(6);
    m.unlock();

    for(int i = 0; i < num; i++)
    {
        m.lock();
        elements[i]->highlight();
        m.unlock();

        SDL_Delay(400 / speed);

        while(getStep() == 0);
        decStep();

        m.lock();
        bool valid = std::to_string(value) == elements[i]->getText();
        if(valid)
        {
            script->highlightLine(7);
            elements[i]->FillWithColor(SDL_Color({10, 155, 10, 255}));
        }else
        {
            elements[i]->FillWithColor(SDL_Color({155, 10, 10, 255}));
        }
        m.unlock();

        SDL_Delay(400 / speed);

        m.lock();
        elements[i]->FillWithColor();
        m.unlock();

        SDL_Delay(400 / speed);

        m.lock();
        elements[i]->unHighlight();
        m.unlock();
        SDL_Delay(200 / speed);
        if(valid) 
        {
            script->unHighlighLine(7);
            break;
        }
    }
    m.lock();
    script->unHighlighLine(5);
    script->unHighlighLine(6);
    script->highlightLine(9);
    m.unlock();

    SDL_Delay(800 / speed);

    m.lock();
    script->unHighlighLine(9);
    m.unlock();
}

void Data_Structures::StaticArrayUpdate(int pos, int value, std::mutex &m)
{

    m.lock();
    for(int i = 0; i < num; i++) elements[i]->show();
    json mem;
    readJson(GLOBAL::AtrbScript + "StaticArrayUpdate.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(3);
    m.unlock();
    SDL_Delay(800 / speed);

    m.lock();
    elements[pos]->highlight();
    script->unHighlighLine(3);
    script->highlightLine(5);
    m.unlock();
    while(getStep() == 0);
    decStep();

    SDL_Delay(800 / speed);

    m.lock();
    script->unHighlighLine(5);
    script->highlightLine(6);
    elements[pos]->setText(std::to_string(value));
    m.unlock();
    SDL_Delay(800 / speed);
    while(getStep() == 0);
    m.lock();
    elements[pos]->unHighlight();
    script->unHighlighLine(6);
    m.unlock();
}
void Data_Structures::SinglyLinkedListUpdate(int pos, int value, std::mutex & m) 
{
    m.lock();
    for(int i = 0; i <  num; i++)
        elements[i]->show();
    m.unlock();

    for(int i = 0; i < pos; i++)
    {
        m.lock();
        elements[i]->highlight();
        m.unlock();

        SDL_Delay(800 / speed);

        m.lock();
        elements[i]->unHighlight();
        m.unlock();
        SDL_Delay(400 / speed);
    }

    m.lock();
    elements[pos]->FillWithColor(SDL_Color{10, 155, 10, 255});
    m.unlock();

    SDL_Delay(400 / speed);
    m.lock();
    elements[pos]->setText(std::to_string(value));
    m.unlock();
    SDL_Delay(800 / speed);

    m.lock();
    elements[pos]->FillWithColor();
    m.unlock();
}

void Data_Structures::DynamicArraySearch(int value, std::mutex &m)
{

    m.lock();
    for(int i = 0; i < num; i++) elements[i]->show();

    json mem;
    readJson(GLOBAL::AtrbScript + "DynamicArraySearch.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(0);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(0);
    script->highlightLine(2);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    for(int i = 0; i < num; i++)
    {
        m.lock();
        elements[i]->highlight();
        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        bool valid = std::to_string(value) == elements[i]->getText();
        if(valid)
        {
            script->highlightLine(4);
            script->highlightLine(5);
            elements[i]->FillWithColor(SDL_Color({10, 155, 10, 255}));
        }else
        {
            elements[i]->FillWithColor(SDL_Color({155, 10, 10, 255}));
        }
        m.unlock();

        SDL_Delay(400 / speed);
        while(getStep() == 0);
        decStep();

        m.lock();
        elements[i]->FillWithColor();
        elements[i]->unHighlight();
        script->unHighlighLine(4);
        script->unHighlighLine(5);
        m.unlock();
        if(valid) break;
    }

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->highlightLine(6);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(6);
    m.unlock();
}

void Data_Structures::StaticArrayErase(int pos, std::mutex &m)
{

    m.lock();
    for(int i = 0; i < num; i++) elements[i]->show();
    json mem;
    readJson(GLOBAL::AtrbScript + "StaticArrayDelete.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(3);
    m.unlock();
    SDL_Delay(1000);

    m.lock();
    script->unHighlighLine(3);
    script->highlightLine(6);
    script->highlightLine(7);
    m.unlock();
    SDL_Delay(300);
    num--;
    for(int i = 0; i < num - 1; i++)
    {
        m.lock();
        elements[i]->highlight();
        elements[i + 1]->highlight();
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

    m.lock();
    script->unHighlighLine(6);
    script->unHighlighLine(7);
    script->highlightLine(8);
    m.unlock();

    SDL_Delay(800 / speed);

    m.lock();
    script->unHighlighLine(8);
    m.unlock();
}

void Data_Structures::DynamicArrayErase(int pos, std::mutex & m)
{

    m.lock();
    for(int i = 0; i < num; i++)
        elements[i]->show();
    json mem;
    readJson(GLOBAL::AtrbScript + "DynamicArrayDelete.json", mem);
    script->loadObject(mem);
    script->loadHighlight(mem["highlight"]);
    script->show();
    script->highlightLine(0);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(0);
    script->highlightLine(1);
    script->highlightLine(2);

    for(int i = 0; i < num - 1; i++)
    {
        elements[i + capacity]->setText("");
        elements[i + capacity]->show();

    }
    m.unlock();

    bool deleted = false;
    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(1);
    script->unHighlighLine(2);
    script->highlightLine(3);
    m.unlock();

    for(int i = 0; i < num; i++)
    {
        if(i == pos)
        {
            deleted = true;

            m.lock();
            elements[i]->FillWithColor(SDL_Color({175, 20, 20, 255}));
            script->highlightLine(5);
            m.unlock();


            SDL_Delay(400 / speed);
            while(getStep() == 0);
            decStep();

            m.lock();
            elements[i]->FillWithColor();
            script->unHighlighLine(5);
            m.unlock();

            SDL_Delay(400 / speed);
            while(getStep() == 0);
            decStep();
        }else 
        {
            m.lock();
            elements[i]->highlight();
            elements[i + capacity - deleted]->highlight();
            script->highlightLine(7);
            m.unlock();


            SDL_Delay(400 / speed);
            while(getStep() == 0);
            decStep();


            m.lock();
            elements[i + capacity - deleted]->setText(elements[i]->getText()); 
            m.unlock();

            SDL_Delay(400 / speed);
            while(getStep() == 0);
            decStep();

            m.lock();
            elements[i]->unHighlight();
            elements[i + capacity - deleted]->unHighlight();
            script->unHighlighLine(7);

            m.unlock();

            SDL_Delay(100 / speed);
            while(getStep() == 0);
            decStep();
        }
    }

    SDL_Delay(200 / speed);
    while(getStep() == 0);
    decStep();


    m.lock();
    script->unHighlighLine(3);
    script->highlightLine(8);
    script->highlightLine(9);
    num--;
    for(int i = 0; i < capacity * 2; i++)
        elements[i]->hide();
    for(int i = 0; i < num; i++)
    {
        elements[i]->setText(elements[i + capacity]->getText());
        elements[i]->show();
    }
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();

    script->unHighlighLine(8);
    script->unHighlighLine(9);
    script->highlightLine(10);
    m.unlock();

    SDL_Delay(400 / speed);
    while(getStep() == 0);
    decStep();

    m.lock();
    script->unHighlighLine(10);
    m.unlock();
}

void Data_Structures::erase(std::string s1, std::mutex &m)
{
    if(num == 0) return ;
    int pos = getFirstInt(s1);
    pos = std::min(pos, num);
    step = -1;
    finish = false;
    if(type == 1) StaticArrayErase(pos, m);
    else if(type == 2) DynamicArrayErase(pos, m);
    else if(type == 3) SinglyLinkedListErase(pos, m);
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
    else if(type == 2) DynamicArrayUpdate(pos, value, m);
    else if(type == 3) SinglyLinkedListUpdate(pos, value, m);
    finish = true;
}

void Data_Structures::search(std::string s2, std::mutex &m)
{
    if(num == 0) return ;
    int value = getFirstInt(s2);
    step = -1;
    finish = false;
    if(type == 1) StaticArraySearch(value, m);
    else if(type == 2) DynamicArraySearch(value, m);
    else if(type == 3) SinglyLinkedListSearch(value, m);
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

void Data_Structures::initDoublyLinkedList(const json &mem)
{
    initSinglyLinkedList(mem);
}

void Data_Structures::initCircularLinkedList(const json &mem)
{
    initCircularLinkedList(mem);
}

void Data_Structures::initSinglyLinkedList(const json & mem)
{
    type = 3;
    Sketch::setRender(ren);
    Sketch::init(mem);

    elements.clear();

    capacity = 9;
    elements.resize(2 * capacity);
    connection.resize(2 * capacity, -1);

    if(mem.contains("circle"))
        circle = mem["circle"];

    if(mem.contains("connect"))
    {
        arrowE = new Object;
        arrowE->init(mem["connect"][0], ren);

        arrowS = new Object;
        arrowS->init(mem["connect"][1], ren);

        arrowW = new Object;
        arrowW->init(mem["connect"][2], ren);

        arrowN = new Object;
        arrowN->init(mem["connect"][3], ren);
    }

    for(int i = 0; i < capacity; i++)
    {
        elements[i] = new Sketch;
        elements[i]->setRender(ren);
        connection[i] = (i + 1 != capacity) ? i + 1 : -1;

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
