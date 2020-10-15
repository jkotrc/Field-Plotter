#define GLEW_STATIC
#include <GL/glew.h>
#include <libfieldplotter/scene.h>

#include <libfieldplotter/vectorfield.h>
#include <libfieldplotter/chargesystem.h>
#include <libfieldplotter/fieldlines.h>

#include <QApplication>
#include "mainwindow.h"

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow win;
    win.show();
    return app.exec();
}
