#include <QApplication>

#include "databaseconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    databaseconfig w;
    w.show();

    return a.exec();
}
