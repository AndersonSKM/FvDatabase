#include "tools.h"
#include <QMessageBox>
#include <QString>

void Menssage(QString texto) {
    QMessageBox::information(NULL,"",texto);
}
