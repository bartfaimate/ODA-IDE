#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTabWidget>
#include <QDialogButtonBox>

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

signals:

public slots:
};

#endif // SETTINGSDIALOG_H
