#include "settings.h"

#include <QFile>
#include <QSettings>
#include <QStandardPaths>

Settings::Settings(QObject *parent) : QObject(parent)
{
    settingsFile = QStandardPaths::locate(
                QStandardPaths::HomeLocation, ".watchonkodi.ini");
    loadSettings();
}

void Settings::loadSettings()
{
    QSettings settings(settingsFile, QSettings::NativeFormat);

    address = settings.value("address", "").toString();
    port = settings.value("port", "").toString();
    username = settings.value("username", "").toString();
    password = settings.value("password", "").toString();
}

void Settings::saveSettings(
        QString _address, QString _port, QString _username, QString _password)
{
    address = _address;
    port = _port;
    username = _username;
    password = _password;

    QSettings settings(settingsFile, QSettings::NativeFormat);

    settings.setValue("address", _address);
    settings.setValue("port", _port);
    settings.setValue("username", _username);
    settings.setValue("password", _password);
}

bool Settings::checkSettingsFile()
{
    if (!QFile(settingsFile).exists()) {
        return false;
    } else {
        return true;
    }
}

QString &Settings::getAddress()
{
    return this->address;
}

QString &Settings::getPort()
{
    return this->port;
}

QString &Settings::getUser()
{
    return this->username;
}

QString &Settings::getPassword()
{
    return this->password;
}
