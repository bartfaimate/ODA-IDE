#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QFontComboBox>
#include <QLabel>
#include <QLineEdit>
#include "settings.h"
#include <QMap>
#include <QDebug>
#include <QSpinBox>


using namespace odaide;

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    this->setGeometry(2000, 100, 400, 600);
    setupLayout();
    this->show();
}

SettingsDialog::~SettingsDialog()
{
    delete this;
}

void SettingsDialog::setupLayout()
{
    createEditorSettingsTab();
    createBuildSettingsTab();
    QVBoxLayout *layout = new QVBoxLayout();
    buttonBox = new QDialogButtonBox();

    this->setLayout(layout);
    buttonBox->addButton(QDialogButtonBox::Ok);
    buttonBox->addButton(QDialogButtonBox::Apply);
    buttonBox->addButton(QDialogButtonBox::Cancel);

    settingTabs = new QTabWidget();
    settingTabs->addTab(editorSettings, tr("Editor settings"));
    settingTabs->addTab(buildSettings, tr("Build settings"));
    layout->addWidget(settingTabs);
    layout->addWidget(buttonBox);
}

void SettingsDialog::connectSignals()
{
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

void SettingsDialog::createEditorSettingsTab()
{
    editorSettings = new QWidget();

    /*font size*/
    QSpinBox *fontSizeEdit = new QSpinBox();
    fontSizeEdit->setRange(1,100);
    fontSizeEdit->setValue(12);
    fontsize = fontSizeEdit->text().toInt();
    /*font family*/
    QFontComboBox *fontComboBox = new QFontComboBox();


    /*tab or spaces*/

    /*Tabwidth*/


    QVBoxLayout *layout = new QVBoxLayout();
    editorSettings->setLayout(layout);

    layout->addWidget(new QLabel(tr("Font Size")));
    layout->addWidget(fontSizeEdit);
    layout->addWidget(new QLabel(tr("Font Family")));
    layout->addWidget(fontComboBox);
}

void SettingsDialog::createBuildSettingsTab()
{
    buildSettings = new QWidget();
}

void SettingsDialog::saveSettings()
{
    QMap<QString, QVariant> whatToSave;
    qDebug() << "saving settings to " << this->editorSettingsFile;

    whatToSave["version"] = "0.1";
    whatToSave["font_size"] = fontsize;
    whatToSave["font_family"] = ;
    odaide::Settings::saveSettings(this->editorSettingsFile, whatToSave);
}

void SettingsDialog::processClick(QAbstractButton *button)
{

}
