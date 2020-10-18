#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "useroptions.h"

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QDialog
{
    Q_OBJECT

public:
    void setOptions(UserOptions& user_options);
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

private slots:
    void on_chargebox1_editingFinished();

    void on_chargebox3_editingFinished();

    void on_chargebox2_editingFinished();

    void on_chargebox4_editingFinished();

    void on_linedensitybox_editingFinished();

    void on_arrowcountbox_editingFinished();

    void on_vfseparationbox_editingFinished();

    void on_dsbox_editingFinished();

    void on_visible_dsbox_editingFinished();

    void on_maxrangebox_editingFinished();

private:
    Ui::OptionsWindow*ui;
};

#endif // DIALOG_H
