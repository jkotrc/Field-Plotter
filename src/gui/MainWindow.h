#pragma once



#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
//#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>




namespace Ui {
    class Canvas;

    class Ui_MainWindow : public QMainWindow {
    public:
        QAction* actionNew;
        QAction* actionOpen;
        QAction* actionSave;
        QAction* actionSave_As;
        QAction* actionShow_Field_Lines;
        QAction* actionShow_Equipotentials;
        QAction* actionExit;
        QWidget* centralwidget;
        //subclass this
        //QOpenGLWidget* openGLWidget;
        Canvas* openGLWidget;
        QPushButton* pushButton;
        QStatusBar* statusbar;
        QMenuBar* menubar;
        QMenu* menuHello;
        QMenu* menuSomething;
        Ui_MainWindow();
        void setupUi();
        void retranslateUi();
    };
}

