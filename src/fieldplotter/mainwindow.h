#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "useroptions.h"

class Scene;
class VectorField;
class Computation;
class FieldLines;
class ChargeSystem;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void initScene();

    void on_actionShow_field_lines_toggled(bool arg1);

    void on_actionShow_field_arrows_toggled(bool arg1);

    void on_actionShow_charges_toggled(bool arg1);

    void on_actionOptions_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    UserOptions options;
    Scene* scene;
    VectorField* vector_field;
    Computation* vector_field_comp;
    FieldLines* field_lines;
    Computation* field_lines_comp;
    ChargeSystem* charge_system;
};

#endif // MAINWINDOW_H
