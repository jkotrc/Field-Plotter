#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class OptionsWindow;
}

class OptionsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsWindow(QWidget *parent = nullptr);
    ~OptionsWindow();

private:
    Ui::OptionsWindow*ui;
};

#endif // DIALOG_H
