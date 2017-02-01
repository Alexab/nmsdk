#include "UGEngineControllWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UGEngineControllWidget w;
    w.show();

    return a.exec();
}
