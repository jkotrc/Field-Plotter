// Field_Plotter.cpp : Defines the entry point for the application.
//

#include "Field_Plotter.h"
#include "gui/MainWindow.h"

#include <QtCore>
#include <iostream>

#define NUM_THREADS 1

//Entry point for the program
int main(int argc, char** argv) {
	std::cout << "Starting...\n";
	QApplication fieldplotter(argc, argv);
	//As per documentation, a QApplication instance needs to exist for the window to show
	Ui::Ui_MainWindow* MainWindow = new Ui::Ui_MainWindow();
	MainWindow->show();
	return fieldplotter.exec();
}