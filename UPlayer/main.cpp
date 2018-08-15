#include "UPlayer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UPlayer w;
    w.show();
    return a.exec();
}
