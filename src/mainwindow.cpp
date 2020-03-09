#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include <QDir>
#include <QMessageBox>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Load settings.
    configSettings = new Settings();
    if (!configSettings->checkSettingsFile()) {
        showMessage("Configure access to Kodi before sending videos.",
                    QMessageBox::Information);
    }

    manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished, this,
            [=](QNetworkReply *reply) {
        if (reply->error()) {
            showMessage(reply->errorString(), QMessageBox::Critical);
            return;
        } else {
            showMessage("Opening video in Kodi...", QMessageBox::Information);
        }
    });
    connect(manager, &QNetworkAccessManager::authenticationRequired, this,
            [=](QNetworkReply *reply, QAuthenticator *authenticator) {
        authenticator->setUser(configSettings->getUser());
        authenticator->setPassword(configSettings->getPassword());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonClear_clicked()
{
    ui->lineEditURL->clear();
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_pushButtonWatch_clicked()
{
    QByteArray videoUrl = ui->lineEditURL->text().toUtf8();
    QByteArray jsonBody = "{\"jsonrpc\":\"2.0\",\"method\":\"Player.Open\",\"params\":{\"item\":{\"file\":\"" + videoUrl + "\"}},\"id\":1}";

    request.setUrl(
                QUrl("http://" + configSettings->getAddress() +
                     ":" + configSettings->getPort() + "/jsonrpc"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(
                QNetworkRequest::ContentLengthHeader,
                QByteArray::number(jsonBody.size()));

    manager->post(request, jsonBody);
}

void MainWindow::showMessage(QString message, QMessageBox::Icon icon)
{
    QMessageBox messageBox;

    messageBox.setText(message);
    messageBox.setIcon(icon);
    messageBox.exec();
}

void MainWindow::on_actionConfigure_triggered()
{
    settingsDialog = new SettingsDialog(this, configSettings);
    settingsDialog->show();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(
           this, "About Watch On Kodi",
           "<b>Minimal desktop app to send a video link to a Kodi system "
           "to reproduce it.</b><br>"
           "<br>Written using Qt5 C++ framework.<br>"
           "<br>This program is licensed under GPL version 3. You can read "
           "<a href=\"https://www.gnu.org/licenses/gpl-3.0.html\">here</a>"
           " the license terms.<br>"
           "<br>The source code is available in "
           "<a href=\"https://github.com/jose-lpa/WatchOnKOdi\">GitHub</a>.");
}

void MainWindow::on_actionUsage_triggered()
{
    QMessageBox::information(
                this, "Usage",
                "<b>Usage instructions:</b><br><br>"
                "<ol>"
                "<li>Configure access to Kodi server endpoint using the "
                "\"Configure\" menu option.</li>"
                "<li>Write down the video URL.</li>"
                "<li>Click \"Watch\" button.");
}
