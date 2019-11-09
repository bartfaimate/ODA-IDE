#ifndef TERMINAL_H
#define TERMINAL_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QObject>
#include <QProcess>
#include <QThread>
#include <iostream>

namespace odaide {
class Terminal: public QPlainTextEdit
{
    Q_OBJECT

public:
    Terminal(QWidget *parent = 0);

    ~Terminal();

signals:

public slots:
    void readProc();

public:
    QProcess *bash;
    QStringList stdOut;

};

class TerminalThread: public QThread
{
  Q_OBJECT

public:
    TerminalThread(QObject *parent = 0);
    TerminalThread(Terminal *console);

    ~TerminalThread();

public slots:
    void start();
    void quit();
    void terminate();

private:
    Terminal *console;
};
}


#endif // TERMINAL_H
