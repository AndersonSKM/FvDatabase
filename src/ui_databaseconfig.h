/********************************************************************************
** Form generated from reading UI file 'databaseconfig.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASECONFIG_H
#define UI_DATABASECONFIG_H

#include <QtGui>
#include <QApplication>
#include <QAction>
#include <QVariant>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_DatabaseConfig
{
public:
    QComboBox *comboBox;
    QLabel *label;
    QLineEdit *edtServer;
    QLabel *label_2;
    QLineEdit *edtUsuario;
    QLabel *label_3;
    QLineEdit *edtSenha;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *sbPorta;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QLineEdit *edtDatabase;
    QLabel *label_6;

    void setupUi(QDialog *DatabaseConfig)
    {
        if (DatabaseConfig->objectName().isEmpty())
            DatabaseConfig->setObjectName(QString::fromUtf8("DatabaseConfig"));
        DatabaseConfig->resize(378, 275);
        comboBox = new QComboBox(DatabaseConfig);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/1444503647_mysql-2048-black.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon, QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(120, 10, 111, 22));
        label = new QLabel(DatabaseConfig);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(12, 13, 91, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(9);
        label->setFont(font);
        edtServer = new QLineEdit(DatabaseConfig);
        edtServer->setObjectName(QString::fromUtf8("edtServer"));
        edtServer->setGeometry(QRect(120, 49, 241, 20));
        label_2 = new QLabel(DatabaseConfig);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 91, 16));
        label_2->setFont(font);
        edtUsuario = new QLineEdit(DatabaseConfig);
        edtUsuario->setObjectName(QString::fromUtf8("edtUsuario"));
        edtUsuario->setGeometry(QRect(120, 79, 241, 20));
        label_3 = new QLabel(DatabaseConfig);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 80, 91, 16));
        label_3->setFont(font);
        edtSenha = new QLineEdit(DatabaseConfig);
        edtSenha->setObjectName(QString::fromUtf8("edtSenha"));
        edtSenha->setGeometry(QRect(120, 109, 241, 20));
        edtSenha->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        label_4 = new QLabel(DatabaseConfig);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 110, 91, 16));
        label_4->setFont(font);
        label_5 = new QLabel(DatabaseConfig);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 172, 91, 16));
        label_5->setFont(font);
        sbPorta = new QSpinBox(DatabaseConfig);
        sbPorta->setObjectName(QString::fromUtf8("sbPorta"));
        sbPorta->setGeometry(QRect(120, 170, 61, 22));
        sbPorta->setMaximum(50000);
        sbPorta->setValue(3306);
        btnOk = new QPushButton(DatabaseConfig);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(200, 240, 75, 23));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icons/Ok.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon1);
        btnCancel = new QPushButton(DatabaseConfig);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(290, 240, 75, 23));
        btnCancel->setLayoutDirection(Qt::LeftToRight);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icons/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnCancel->setIcon(icon2);
        edtDatabase = new QLineEdit(DatabaseConfig);
        edtDatabase->setObjectName(QString::fromUtf8("edtDatabase"));
        edtDatabase->setGeometry(QRect(120, 139, 241, 20));
        edtDatabase->setEchoMode(QLineEdit::Normal);
        label_6 = new QLabel(DatabaseConfig);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 140, 91, 16));
        label_6->setFont(font);

        retranslateUi(DatabaseConfig);

        QMetaObject::connectSlotsByName(DatabaseConfig);
    } // setupUi

    void retranslateUi(QDialog *DatabaseConfig)
    {
        DatabaseConfig->setWindowTitle(QApplication::translate("DatabaseConfig", "DatabaseConfig", 0));
        comboBox->setItemText(0, QApplication::translate("DatabaseConfig", "MySQL ", 0));

        label->setText(QApplication::translate("DatabaseConfig", "Database Driver:", 0));
        label_2->setText(QApplication::translate("DatabaseConfig", "Servidor / IP:", 0));
        label_3->setText(QApplication::translate("DatabaseConfig", "Usu\303\241rio:", 0));
        label_4->setText(QApplication::translate("DatabaseConfig", "Senha:", 0));
        label_5->setText(QApplication::translate("DatabaseConfig", "Porta:", 0));
        btnOk->setText(QApplication::translate("DatabaseConfig", "Abrir", 0));
        btnCancel->setText(QApplication::translate("DatabaseConfig", "Cancelar", 0));
        label_6->setText(QApplication::translate("DatabaseConfig", "Banco de Dados:", 0));
    } // retranslateUi

};

namespace Ui {
    class DatabaseConfig: public Ui_DatabaseConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASECONFIG_H
