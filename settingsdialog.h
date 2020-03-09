#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "settings.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(
            QWidget *parent = nullptr, Settings *settings = nullptr);
    ~SettingsDialog();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::SettingsDialog *ui;

    Settings *configSettings;
};

#endif // SETTINGSDIALOG_H
