#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QLabel>

#include <QStatusBar>

class StatusBar : public QStatusBar
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);
    ~StatusBar();


    void setFileExtension(QString extension);
private:
    QLabel *fileExtensionLabel;

signals:

public slots:
};

#endif // STATUSBAR_H
