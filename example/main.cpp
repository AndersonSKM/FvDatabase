#include <QApplication>
#include <QDebug>

#include "configconnection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("LaycanExemple");
    QApplication::setOrganizationName("Laycan");
    QApplication::setOrganizationDomain("www.github.com/AndersonSKM/Laycan");
    QApplication::setApplicationVersion("1.0");

    int returnCode = EXIT_FAILURE;

    try {

        ConfigConnection w;
        w.show();

        returnCode = a.exec();
    } catch (std::exception &e) {
        qDebug() << e.what();
    } catch (...) {
        qDebug() << "An unhandled exception has been thrown.";
    }

    qDebug() << QString("Application terminated with return code %1.").arg(returnCode);

    return returnCode;
}
