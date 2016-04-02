#include "laycaneditor.h"
#include "dlgopenfile.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DlgOpenFile dlg;
    dlg.show();

    return a.exec();
}
