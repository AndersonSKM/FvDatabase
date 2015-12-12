#include <QApplication>
#include <QDir>
#include <QDebug>

#include "databaseconfig.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseConfig w;
    w.show();

    return a.exec();
}
