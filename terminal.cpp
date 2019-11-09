#include "terminal.h"

odaide::Terminal::Terminal(QWidget *parent)  : QPlainTextEdit(parent)
{
    std::cout << "Hello Terminal\n";
    this->appendPlainText("Terminal");

    bash = new QProcess();
    QObject::connect(bash, SIGNAL(readyReadStdError()), this, SLOT(appendPlainText()));
    QObject::connect(bash, SIGNAL(readyReadStdOutput()), this, SLOT(readProc()));
//    bash->execute("bash");

}

odaide::Terminal::~Terminal()
{
    std::cout << "Goodbye Terminal\n";

}




odaide::TerminalThread::TerminalThread(QObject *parent): QThread(parent)
{
//    this->console = new Terminal();

}

odaide::TerminalThread::TerminalThread(Terminal *console)
{
    this->console = console;
}

odaide::TerminalThread::~TerminalThread()
{

}

void odaide::TerminalThread::start()
{
    std::cout << "start\n";
    std::cout.flush();

    console->bash->execute("echo hello bash");
}

void odaide::TerminalThread::quit()
{


}

void odaide::TerminalThread::terminate()
{

}
