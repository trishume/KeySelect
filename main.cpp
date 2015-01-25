#include "debugwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DebugWindow w;
    w.show();

    return a.exec();
}
