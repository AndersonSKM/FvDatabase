#include <QApplication>

#include "configconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConfigConnection w;
    w.show();

    return a.exec();
}
