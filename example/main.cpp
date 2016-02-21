#include <QApplication>

#include "configconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("LaycanExemple");
    QApplication::setOrganizationName("Laycan");
    QApplication::setOrganizationDomain("www.github.com/AndersonSKM/Laycan");
    QApplication::setApplicationVersion("1.0");

    ConfigConnection w;
    w.show();

    return a.exec();
}
