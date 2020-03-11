#include "settings.h"

#include <QSettings>

Settings::Settings(QObject *parent) : QObject(parent)
{
    loadSettings();
}

void Settings::loadSettings()
{
    QSettings settings("VASSLogic", "WatchOnKodi");

    settings.beginGroup("KodiAccess");
    address = settings.value("address", "").toString();
    port = settings.value("port", "8080").toString();
    username = settings.value("username", "").toString();
    password = settings.value("password", "").toString();
    settings.endGroup();
}

void Settings::saveSettings(
        QString _address, QString _port, QString _username, QString _password)
{
    address = _address;
    port = _port;
    username = _username;
    password = _password;

    QSettings settings("VASSLogic", "WatchOnKodi");

    settings.beginGroup("KodiAccess");
    settings.setValue("address", _address);
    settings.setValue("port", _port);
    settings.setValue("username", _username);
    settings.setValue("password", _password);
    settings.endGroup();
}

bool Settings::checkSettingsFile()
{
    QSettings settings("VASSLogic", "WatchOnKodi");

    settings.beginGroup("KodiAccess");
    if (settings.value("address", "") == "")
        return false;

    return true;
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
