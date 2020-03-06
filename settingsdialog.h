#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QButtonGroup>

namespace odaide {
class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
private:
    void setupLayout();
    void connectSignals();
    void createEditorSettingsTab();
    void createBuildSettingsTab();



private:
    QWidget *editorSettings;
    QWidget *buildSettings;
    QTabWidget *settingTabs;
    QDialogButtonBox *buttonBox;


    QString configFolder = "configs/";
    QString editorSettingsFile = configFolder + "editor_settings.ini";

    int fontsize;
    QString fontFamily;

signals:

public slots:
    void saveSettings();

private slots:
    void processClick(QAbstractButton *button);
};
}


#endif // SETTINGSDIALOG_H
