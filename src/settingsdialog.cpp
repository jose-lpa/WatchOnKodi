#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent, Settings *settings) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    configSettings = settings;

    // Validate IP address input.
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegularExpression ipRegex(
                "^" + ipRange + "\\." + ipRange + "\\." + ipRange + "\\."
                + ipRange + "$");
    QRegularExpressionValidator *ipValidator = new QRegularExpressionValidator(
                ipRegex);

    ui->lineEditAddress->setValidator(ipValidator);
    ui->lineEditAddress->setText(configSettings->getAddress());
    ui->spinBoxPort->setValue(configSettings->getPort().toInt());
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
                ui->spinBoxPort->text(),
                ui->lineEditUser->text(),
                ui->lineEditPassword->text());

    this->close();
}
