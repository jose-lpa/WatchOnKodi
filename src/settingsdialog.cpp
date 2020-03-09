#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent, Settings *settings) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    configSettings = settings;

    ui->lineEditAddress->setText(configSettings->getAddress());
    ui->lineEditPort->setText(configSettings->getPort());
    ui->lineEditUser->setText(configSettings->getUser());
    ui->lineEditPassword->setText(configSettings->getPassword());
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_rejected()
{
    this->close();
}

void SettingsDialog::on_buttonBox_accepted()
{
    configSettings->saveSettings(
                ui->lineEditAddress->text(),
                ui->lineEditPort->text(),
                ui->lineEditUser->text(),
                ui->lineEditPassword->text());

    this->close();
}