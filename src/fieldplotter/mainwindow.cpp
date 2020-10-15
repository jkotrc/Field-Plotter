#define GLEW_STATIC
#include <GL/glew.h>
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "optionswindow.h"

#include <libfieldplotter/scene.h>
#include <libfieldplotter/chargesystem.h>
#include <libfieldplotter/fieldlines.h>
#include <libfieldplotter/vectorfield.h>

const int N = 3;
PointCharge singlecharge[N] = {
    PointCharge(Point(0.0f, 0.0f, 0.5f), 0.1f),
    PointCharge(Point(0.0f, 0.0f, -0.5f), -0.1f),
    PointCharge(Point(0.0f, 0.5f, 0.0f), 0.1f)
};
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    options = UserOptions();
    ui->setupUi(this);
    QObject::connect(ui->openGLWidget, &Canvas::glReady, this, &MainWindow::initScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initScene() {
    scene = ui->openGLWidget->getScene();
    field_lines = new FieldLines(options.maxrange, options.computational_step, options.line_density);
    charge_system = new ChargeSystem(N, singlecharge);
    vector_field = new VectorField(options.arrow_spatial_separation, options.arrow_count);
    field_lines_comp = new Computation(field_lines, *charge_system, compute_field_lines);
    vector_field_comp = new Computation(vector_field, *charge_system, compute_electric_field);
    scene->addComponent(*charge_system);
}



void MainWindow::on_actionShow_field_lines_toggled(bool arg1)
{
    if (arg1) {
        if (!field_lines->isComputed()) {
            field_lines_comp->spawnThread();
            
        }
        //comp->spawnThread();
        scene->addComponent(*field_lines);
    }
    else {
        field_lines->detach();
    }
}

void MainWindow::on_actionShow_field_arrows_toggled(bool arg1)
{
    if (arg1) {
        if (!vector_field->isComputed()) {
            compute_electric_field(vector_field, *charge_system); //vector fields are so inexpensive that this does not even need a thread (which does not work right now XD)
            //vector_field_comp->spawnThread();
        }
        scene->addComponent(*vector_field);
    }
    else {
        vector_field->detach();
    }
}

void MainWindow::on_actionShow_charges_toggled(bool arg1)
{
    if (arg1) {
        scene->addComponent(*charge_system);
    }
    else {
        charge_system->detach();
    }
}

void MainWindow::on_actionOptions_triggered()
{
    OptionsWindow win;
    win.setModal(true);
    win.exec();
}

void MainWindow::on_actionAbout_triggered()
{

}
