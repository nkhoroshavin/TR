#include "kommi.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kommi w;
    w.show();
    return a.exec();
}
