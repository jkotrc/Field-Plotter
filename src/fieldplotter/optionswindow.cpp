#include "optionswindow.h"
#include "ui_optionswindow.h"

#include <QString>
OptionsWindow::OptionsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsWindow)
{
    ui->setupUi(this);
}


/*
There is no user field for:
float ball_radius;
*/
void OptionsWindow::setOptions(UserOptions& user_options) {
    ui->visible_dsbox->setText(QString::number(user_options.visible_step));
    ui->dsbox->setText(QString::number(user_options.computational_step));
    ui->vfseparationbox->setText(QString::number(user_options.arrow_spatial_separation));
    ui->arrowcountbox->setText(QString::number(user_options.arrow_count));
    ui->maxrangebox->setText(QString::number(user_options.maxrange));
    ui->linedensitybox->setText(QString::number(user_options.line_density));
    
    //TODO: This is horrible. Please fix
    ui->chargebox1->setText(QString::fromStdString(user_options.charges[0]));
    ui->chargebox2->setText(QString::fromStdString(user_options.charges[1]));
    ui->chargebox3->setText(QString::fromStdString(user_options.charges[2]));
    ui->chargebox4->setText(QString::fromStdString(user_options.charges[3]));
}

OptionsWindow::~OptionsWindow()
{
    delete ui;
}



void OptionsWindow::on_chargebox1_editingFinished()
{

}

void OptionsWindow::on_chargebox3_editingFinished()
{

}

void OptionsWindow::on_chargebox2_editingFinished()
{

}

void OptionsWindow::on_chargebox4_editingFinished()
{

}

void OptionsWindow::on_linedensitybox_editingFinished()
{
    //TODO: Not yet implemented in libfieldplotter
}

void OptionsWindow::on_arrowcountbox_editingFinished()
{

}

void OptionsWindow::on_vfseparationbox_editingFinished()
{

}

void OptionsWindow::on_dsbox_editingFinished()
{

}

void OptionsWindow::on_visible_dsbox_editingFinished()
{

}

void OptionsWindow::on_maxrangebox_editingFinished()
{

}
