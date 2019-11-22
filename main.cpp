#include "mainwindow.h"
#include <QApplication>
#include "settingsdialog.h"

#include <iostream>

int main(int argc, char *argv[])
{
#ifdef IDE
QApplication app(argc, argv);
MainWindow window;
window.show();

return app.exec();
#endif
#ifdef SETTINGS
    std::cout <<"Settings\n";
    QApplication app(argc, argv);
    SettingsDialog window;
    window.show();

    return app.exec();



#endif

}
