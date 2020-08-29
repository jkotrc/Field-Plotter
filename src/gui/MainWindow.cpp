/********************************************************************************
** Form generated from reading UI file 'window-designbyfLpm.ui'
** --- With some modifications that make it fit better into the project
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include "MainWindow.h"
#include "GraphicsCanvas.h"

#include <iostream>


using namespace Ui;


Ui_MainWindow::Ui_MainWindow()
    : QMainWindow()
{
    this->setupUi();
}

void Ui_MainWindow::setupUi()
//trying to replace QMainWindow *MainWindow with self
{
    if (this->objectName().isEmpty())
        this->setObjectName(QString::fromUtf8("MainWindow"));
    this->resize(800, 600);
    actionNew = new QAction(this);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    actionOpen = new QAction(this);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionSave = new QAction(this);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    actionSave->setEnabled(false);
    actionSave_As = new QAction(this);
    actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
    actionSave_As->setEnabled(false);
    actionShow_Field_Lines = new QAction(this);
    actionShow_Field_Lines->setObjectName(QString::fromUtf8("actionShow_Field_Lines"));
    actionShow_Field_Lines->setEnabled(false);
    actionShow_Equipotentials = new QAction(this);
    actionShow_Equipotentials->setObjectName(QString::fromUtf8("actionShow_Equipotentials"));
    actionShow_Equipotentials->setEnabled(false);
    actionExit = new QAction(this);
    actionExit->setObjectName(QString::fromUtf8("actionExit"));
    centralwidget = new QWidget(this);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));

    openGLWidget = new Ui::Canvas(centralwidget);
    openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
    openGLWidget->setGeometry(QRect(0, 0, 801, 521));

    pushButton = new QPushButton(centralwidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(360, 530, 75, 23));
    this->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    this->setStatusBar(statusbar);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 21));
    menuHello = new QMenu(menubar);
    menuHello->setObjectName(QString::fromUtf8("menuHello"));
    menuSomething = new QMenu(menubar);
    menuSomething->setObjectName(QString::fromUtf8("menuSomething"));
    this->setMenuBar(menubar);

    menubar->addAction(menuHello->menuAction());
    menubar->addAction(menuSomething->menuAction());
    menuHello->addAction(actionNew);
    menuHello->addAction(actionOpen);
    menuHello->addAction(actionSave);
    menuHello->addAction(actionSave_As);
    menuHello->addAction(actionExit);
    menuSomething->addAction(actionShow_Field_Lines);
    menuSomething->addAction(actionShow_Equipotentials);

    retranslateUi();

    QMetaObject::connectSlotsByName(this);
} // setupUi

void Ui_MainWindow::retranslateUi()
{
    this->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    actionNew->setText(QCoreApplication::translate("MainWindow", "New Computation", nullptr));
#if QT_CONFIG(shortcut)
    actionNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
    actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
    actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
    actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
    actionSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
    actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As..", nullptr));
#if QT_CONFIG(shortcut)
    actionSave_As->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
    actionShow_Field_Lines->setText(QCoreApplication::translate("MainWindow", "Show Field Lines", nullptr));
    actionShow_Equipotentials->setText(QCoreApplication::translate("MainWindow", "Show Equipotentials", nullptr));
    actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
#if QT_CONFIG(shortcut)
    actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
    pushButton->setText(QCoreApplication::translate("MainWindow", "Bottom Text", nullptr));
    menuHello->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
    menuSomething->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
} // retranslateUi



//namespace Ui {
//    class MainWindow: public Ui_MainWindow {};
//} // namespace Ui


