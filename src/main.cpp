#include <DuckWin.hpp>


int main()
{
    MyWindow* mainWin = new MyWindow;

    mainWin->init();

    while(mainWin->isOpen())
    {
        mainWin->action();
    }

    return 0;
}
