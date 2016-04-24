/********************************************************************************
** Form generated from reading UI file 'laycaneditorview.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYCANEDITORVIEW_H
#define UI_LAYCANEDITORVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_laycaneditorview
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
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
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeMigrations;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;

    void setupUi(QMainWindow *laycaneditorview)
    {
        if (laycaneditorview->objectName().isEmpty())
            laycaneditorview->setObjectName(QStringLiteral("laycaneditorview"));
        laycaneditorview->setWindowModality(Qt::NonModal);
        laycaneditorview->resize(867, 570);
        centralwidget = new QWidget(laycaneditorview);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(260, 10, 591, 531));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        edVersion = new QLineEdit(layoutWidget);
        edVersion->setObjectName(QStringLiteral("edVersion"));
        edVersion->setMaximumSize(QSize(16777215, 16777204));

        horizontalLayout_2->addWidget(edVersion);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        edDescription = new QLineEdit(layoutWidget);
        edDescription->setObjectName(QStringLiteral("edDescription"));

        horizontalLayout_3->addWidget(edDescription);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_4);

        tabScripts = new QTabWidget(layoutWidget);
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

        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 229, 531));
        verticalLayout = new QVBoxLayout(layoutWidget_2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        treeMigrations = new QTreeWidget(layoutWidget_2);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeMigrations->setHeaderItem(__qtreewidgetitem);
        treeMigrations->setObjectName(QStringLiteral("treeMigrations"));
        treeMigrations->header()->setVisible(false);

        verticalLayout->addWidget(treeMigrations);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(layoutWidget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/cross.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setFlat(false);

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);
        pushButton_2->setFlat(false);

        horizontalLayout->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        laycaneditorview->setCentralWidget(centralwidget);
        menubar = new QMenuBar(laycaneditorview);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 867, 22));
        laycaneditorview->setMenuBar(menubar);

        retranslateUi(laycaneditorview);

        tabScripts->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(laycaneditorview);
    } // setupUi

    void retranslateUi(QMainWindow *laycaneditorview)
    {
        laycaneditorview->setWindowTitle(QApplication::translate("laycaneditorview", "MainWindow", 0));
        label->setText(QApplication::translate("laycaneditorview", "Version", 0));
        label_2->setText(QApplication::translate("laycaneditorview", "Description", 0));
        tabScripts->setTabText(tabScripts->indexOf(tabUpVersion), QApplication::translate("laycaneditorview", "Up Version", 0));
        tabScripts->setTabText(tabScripts->indexOf(tabDownVersion), QApplication::translate("laycaneditorview", "Down Version", 0));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class laycaneditorview: public Ui_laycaneditorview {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYCANEDITORVIEW_H
