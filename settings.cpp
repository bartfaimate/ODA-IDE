#include "settings.h"
#include <QSettings>

Settings::Settings()
{

}

bool Settings::saveSettings(const QString path, QMap<QString, QVariant> whatToSave)
{
    bool success = false;
    try {
        QSettings settings(path, QSettings::IniFormat);

        for(auto key : whatToSave.keys()) {

            /* setup window position and size */
            settings.setValue(key, whatToSave.value(key));
         }
        success = true;
    }
    catch(...) {
            success = false;
    }
    return  success;
}

bool Settings::loadSettings(const QString path, QMap<QString, QVariant> &whatToLoad)
{
    bool success = false;
    try {
        QSettings settings(path, QSettings::IniFormat); /* load settings */
        QStringList keys = settings.allKeys();

        for(auto key: keys) {
            whatToLoad[key] = settings.value(key);
        }
        success = true;
    } catch (...) {
        success = false;
    }

    return success;
}
