#include "statusbar.h"

StatusBar::StatusBar(QWidget *parent) : QStatusBar (parent)
{
    this->fileExtensionLabel = new QLabel(this);
    this->addWidget(new QLabel(tr("Filetype: ")));
    this->addWidget(fileExtensionLabel);
}

StatusBar::~StatusBar()
{

}

void StatusBar::setFileExtension(QString extension)
{

    this->fileExtensionLabel->setText(extension);

}
