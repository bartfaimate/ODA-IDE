#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QMap>

namespace odaide {
class Settings
{
public:
    Settings();
    ~Settings();

    static bool saveSettings(const QString path, QMap<QString, QVariant> whatToSave);
    static bool loadSettings(const QString path, QMap<QString, QVariant> &whatToLoad);
};

}


#endif // SETTINGS_H
