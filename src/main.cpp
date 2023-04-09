#include <DuckWin.hpp>


int main()
{
    MyWindow* mainWin = new MyWindow;

    mainWin->init();
    mainWin->changeScreens("home.json");
    
    mainWin->run();

    delete mainWin;

    return 0;
}
