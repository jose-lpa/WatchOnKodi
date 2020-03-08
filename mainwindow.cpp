#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QByteArray>
#include <QMessageBox>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkReply>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished, this,
            [=](QNetworkReply *reply) {
        if (reply->error()) {
            showMessage(reply->errorString());
            return;
        } else {
            showMessage("Opening video in Kodi...");
        }
    });

    connect(manager, &QNetworkAccessManager::authenticationRequired, this,
            [=](QNetworkReply *reply, QAuthenticator *authenticator) {
        authenticator->setUser("cloudigital");
        authenticator->setPassword("kodi");
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

    request.setUrl(QUrl("http://192.168.0.200:8080/jsonrpc"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(
                QNetworkRequest::ContentLengthHeader,
                QByteArray::number(jsonBody.size()));

    manager->post(request, jsonBody);
}

void MainWindow::showMessage(QString message)
{
    QMessageBox messageBox;

    messageBox.setText(message);
    messageBox.exec();
}
