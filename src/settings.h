#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

class Settings : public QObject
{
    Q_OBJECT

public:
    explicit Settings(QObject *parent = nullptr);

    QString &getAddress();
    QString &getPort();
    QString &getUser();
    QString &getPassword();
    bool checkSettingsFile();
    void saveSettings(
            QString _address, QString _port, QString _username,
            QString _password);

private:
    QString address = "";
    QString port = "";
    QString username = "";
    QString password = "";

    void loadSettings();
};

#endif // SETTINGS_H
