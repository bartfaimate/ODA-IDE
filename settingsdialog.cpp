#include "settingsdialog.h"
#include <QVBoxLayout>
#include <QFontComboBox>
#include <QLabel>
#include <QLineEdit>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    this->setGeometry(2000, 100, 400, 600);
    setupLayout();
    this->show();
}

SettingsDialog::~SettingsDialog()
{

}

/**
 * @brief SettingsDialog::setupLayout
 */
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

/**
 * @brief SettingsDialog::connectSignals
 */
void SettingsDialog::connectSignals()
{
    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

/**
 * @brief SettingsDialog::createEditorSettingsTab
 */
void SettingsDialog::createEditorSettingsTab()
{
    editorSettings = new QWidget();

    /*font size*/
    QLineEdit *fontSizeEdit = new QLineEdit();
    fontSizeEdit->setText("12");
    int fontsize = fontSizeEdit->text().toInt();
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

/**
 * @brief SettingsDialog::createBuildSettingsTab
 */
void SettingsDialog::createBuildSettingsTab()
{
    buildSettings = new QWidget();
}
