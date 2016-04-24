/********************************************************************************
** Form generated from reading UI file 'dlgopenfile.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGOPENFILE_H
#define UI_DLGOPENFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DlgOpenFile
{
public:
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *edtFile;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpen;
    QPushButton *btnCancel;

    void setupUi(QDialog *DlgOpenFile)
    {
        if (DlgOpenFile->objectName().isEmpty())
            DlgOpenFile->setObjectName(QStringLiteral("DlgOpenFile"));
        DlgOpenFile->setWindowModality(Qt::WindowModal);
        DlgOpenFile->resize(380, 98);
        layoutWidget = new QWidget(DlgOpenFile);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 363, 83));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        edtFile = new QLineEdit(layoutWidget);
        edtFile->setObjectName(QStringLiteral("edtFile"));

        horizontalLayout_2->addWidget(edtFile);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setFlat(false);

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(178, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnOpen = new QPushButton(layoutWidget);
        btnOpen->setObjectName(QStringLiteral("btnOpen"));

        horizontalLayout->addWidget(btnOpen);

        btnCancel = new QPushButton(layoutWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));

        horizontalLayout->addWidget(btnCancel);


        horizontalLayout_3->addLayout(horizontalLayout);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);


        formLayout->setLayout(0, QFormLayout::LabelRole, verticalLayout_2);


        retranslateUi(DlgOpenFile);

        btnOpen->setDefault(true);


        QMetaObject::connectSlotsByName(DlgOpenFile);
    } // setupUi

    void retranslateUi(QDialog *DlgOpenFile)
    {
        DlgOpenFile->setWindowTitle(QApplication::translate("DlgOpenFile", "Select Your Migration Xml File", 0));
        pushButton->setText(QApplication::translate("DlgOpenFile", "&Choose...", 0));
        btnOpen->setText(QApplication::translate("DlgOpenFile", "&Open", 0));
        btnCancel->setText(QApplication::translate("DlgOpenFile", "&Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgOpenFile: public Ui_DlgOpenFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGOPENFILE_H
