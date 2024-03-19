#include <QtWidgets/QApplication>
#include "GUI.h"

void TestAll()
{
    testeRepo();
    testValidator();
    testService();
}

int main(int argc, char* argv[])
{
    TestAll();
    QApplication a(argc, argv);
    Repo rep;
    ProdusValidator val;
    Cos cos;
    Service serv{ rep,val,cos };
    Gui gui{ serv };

    gui.show();

    return a.exec();
}
