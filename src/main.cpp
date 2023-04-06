#include <DuckWin.hpp>


int main()
{
    MyWindow* mainWin = new MyWindow;

    mainWin->init();
    mainWin->changeScreens("home.json");
    
    while(mainWin->isOpen())
    {
        mainWin->render();
        mainWin->action();
    }

    delete mainWin;

    return 0;
}
