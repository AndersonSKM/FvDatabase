/********************************************************************************
** Form generated from reading UI file 'laycaneditor.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYCANEDITOR_H
#define UI_LAYCANEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LaycanEditor
{
public:
    QAction *actionAbout;
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeMigrations;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *edVersion;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *edDescription;
    QTabWidget *tabScripts;
    QWidget *tabUpVersion;
    QTextBrowser *textBrowser;
    QWidget *tabDownVersion;
    QTextBrowser *textBrowser_2;
    QMenuBar *menuBar;
    QMenu *menuHelp;

    void setupUi(QMainWindow *LaycanEditor)
    {
        if (LaycanEditor->objectName().isEmpty())
            LaycanEditor->setObjectName(QStringLiteral("LaycanEditor"));
        LaycanEditor->setWindowModality(Qt::NonModal);
        LaycanEditor->resize(886, 604);
        LaycanEditor->setToolButtonStyle(Qt::ToolButtonIconOnly);
        actionAbout = new QAction(LaycanEditor);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(LaycanEditor);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 229, 531));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeMigrations = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeMigrations->setHeaderItem(__qtreewidgetitem);
        treeMigrations->setObjectName(QStringLiteral("treeMigrations"));
        treeMigrations->header()->setVisible(false);

        verticalLayout->addWidget(treeMigrations);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setFlat(false);

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        layoutWidget1 = new QWidget(centralWidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(270, 20, 591, 531));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        edVersion = new QLineEdit(layoutWidget1);
        edVersion->setObjectName(QStringLiteral("edVersion"));
        edVersion->setMaximumSize(QSize(16777215, 16777204));

        horizontalLayout_2->addWidget(edVersion);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        edDescription = new QLineEdit(layoutWidget1);
        edDescription->setObjectName(QStringLiteral("edDescription"));

        horizontalLayout_3->addWidget(edDescription);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tabScripts = new QTabWidget(layoutWidget1);
        tabScripts->setObjectName(QStringLiteral("tabScripts"));
        tabUpVersion = new QWidget();
        tabUpVersion->setObjectName(QStringLiteral("tabUpVersion"));
        textBrowser = new QTextBrowser(tabUpVersion);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(0, 0, 581, 471));
        tabScripts->addTab(tabUpVersion, QString());
        tabDownVersion = new QWidget();
        tabDownVersion->setObjectName(QStringLiteral("tabDownVersion"));
        textBrowser_2 = new QTextBrowser(tabDownVersion);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(0, 0, 581, 471));
        tabScripts->addTab(tabDownVersion, QString());

        verticalLayout_2->addWidget(tabScripts);

        LaycanEditor->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LaycanEditor);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 886, 22));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        LaycanEditor->setMenuBar(menuBar);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(LaycanEditor);

        tabScripts->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(LaycanEditor);
    } // setupUi

    void retranslateUi(QMainWindow *LaycanEditor)
    {
        LaycanEditor->setWindowTitle(QApplication::translate("LaycanEditor", "LaycanEditor", 0));
        actionAbout->setText(QApplication::translate("LaycanEditor", "About", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        label->setText(QApplication::translate("LaycanEditor", "Version", 0));
        label_2->setText(QApplication::translate("LaycanEditor", "Description", 0));
        tabScripts->setTabText(tabScripts->indexOf(tabUpVersion), QApplication::translate("LaycanEditor", "Up Version", 0));
        tabScripts->setTabText(tabScripts->indexOf(tabDownVersion), QApplication::translate("LaycanEditor", "Down Version", 0));
        menuHelp->setTitle(QApplication::translate("LaycanEditor", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class LaycanEditor: public Ui_LaycanEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYCANEDITOR_H
