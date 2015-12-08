#include "databaseconfig.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DatabaseConfig w;
    w.show();

    return a.exec();
}
