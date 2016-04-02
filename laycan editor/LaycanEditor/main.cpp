#include "laycaneditor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LaycanEditor w;
    w.show();

    return a.exec();
}
