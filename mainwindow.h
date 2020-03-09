#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QUrl>

#include "settings.h"
#include "settingsdialog.h"

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
    void on_pushButtonClear_clicked();
    void on_actionQuit_triggered();
    void on_pushButtonWatch_clicked();
    void on_actionConfigure_triggered();
    void on_actionAbout_triggered();
    void on_actionUsage_triggered();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    Settings *configSettings;
    SettingsDialog *settingsDialog;

    void showMessage(QString message, QMessageBox::Icon icon);
};

#endif // MAINWINDOW_H
