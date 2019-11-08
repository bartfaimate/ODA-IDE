#include "mainwindow.h"
#include <iostream>
#include <QLabel>
#include <QTextStream>
#include <QMessageBox>
#include "highlighter.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(100, 100, 640, 480);

    this->createLayout();
    this->createActions();
    this->createMenus();
    this->createButtons();
    this->loadSettings();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createLayout()
{
    /* widget is mainwidget*/
    QWidget *mainWidget = new QWidget;
    setCentralWidget(mainWidget);
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->windowStatusBar = new StatusBar;
    this->setStatusBar(this->windowStatusBar);

    this->createStatusBar();

    hBoxLayout = new QHBoxLayout(); /* horizontal layout */

    verticalSplitter = new QSplitter(); /* vertical splitter for the file system view */
    verticalSplitter->setOrientation(Qt::Vertical);
    horizontalSplitter = new QSplitter(Qt::Horizontal); /* horizontal splitter for the debug console and text editor */

    menuBar = new QMenuBar(topFiller);  /* menubar to the top */
    toolBar = new QToolBar(topFiller);  /* toolbar to the top, under menubar */

    fileManager = new FileManager();
    horizontalSplitter->addWidget(fileManager);
    horizontalSplitter->addWidget(verticalSplitter);

    // set sizepolicy for horizontalsplitter
    horizontalSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    editorTabs = new QTabWidget();       /* tab widget to the splitter */
    editorTabs->setMovable(true);
    editorTabs->setTabsClosable(true);
    connect(editorTabs, SIGNAL(tabCloseRequested(int)), this, SLOT(closeTab(int)));

    outputTabs = new QTabWidget();
    outputTabs->setMovable(true);
    verticalSplitter->addWidget(editorTabs);
    verticalSplitter->addWidget(outputTabs);
//      verticalSplitter->addWidget(console);   /* console under the tab */

    //most jó a file menü gomb, viszont splitter nem
    QVBoxLayout *vBoxLayout = new QVBoxLayout(); /* vertical layout */
    vBoxLayout->setMargin(5);
    vBoxLayout->addWidget(menuBar);
    vBoxLayout->addWidget(toolBar);
    vBoxLayout->addLayout(hBoxLayout);
    vBoxLayout->addWidget(horizontalSplitter);
    //   vBoxLayout->addWidget(tab);

    mainWidget->setLayout(vBoxLayout);
    hBoxLayout->addWidget(toolBar);
    this->setLayout(hBoxLayout);

    this->editorTabs->addTab(new Editor(), tr("New File"));      /* add the first tab with editor */

    this->createTerminal();
    this->outputTabs->addTab(console, tr("Terminal"));
    this->outputTabs->addTab(new QWidget(), tr("Debug"));
    this->outputTabs->addTab(new QWidget(), tr("Output"));

//    QWidget *console = new odaide::Terminal();
//    consoleThread = new odaide::TerminalThread(console);





    connect(this->editorTabs, SIGNAL(currentChanged(int)), this, SLOT(updateStatusbar(int)));
    connect(this->fileManager, SIGNAL(signalFilePath(QString)), this, SLOT(openFile(QString)));
//    consoleThread->start();

}

void MainWindow::createMenus()
{
    createFileMenu();
    createEditMenu();
    createCompileMenu();
    createHelpMenu();

}

void MainWindow::createFileMenu()
{
    fileMenu = menuBar->addMenu(tr("&File"));
    fileMenu->addAction(newWindowAct);
    fileMenu->addAction(newProjectAct);
//    fileMenu->addAction(newTabAct);
    fileMenu->addAction(newFileAct);
    fileMenu->addAction(openFileAct);
    fileMenu->addAction(openFolderAct);
    fileMenu->addAction(saveFileAct);
    fileMenu->addAction(saveFileAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void MainWindow::createEditMenu()
{
    editMenu = menuBar->addMenu(tr("&Edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);

}

void MainWindow::createCompileMenu()
{
    compilerMenu = menuBar->addMenu(tr("Com&piler"));
    compilerMenu->addAction(compileAct);
    compilerMenu->addAction(buildAct);
    compilerMenu->addAction(makeAct);
    compilerMenu->addAction(runAct);
    compilerMenu->addSeparator();
    compilerMenu->addAction(buildSettingsAct);

}

void MainWindow::createHelpMenu()
{
    helpMenu = menuBar->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createButtons()
{
//    /*NEW TAB*/
//    newTabButton = new QPushButton(*newTabIcon, tr("New Tab"));
//    toolBar->addWidget(newTabButton);
//    connect(newTabButton, SIGNAL(clicked(bool)), this, SLOT(addTab()));
//    newTabButton->setToolTip(tr("New tab"));

    /* NEW FILE*/
    newFileButton = new QPushButton(*newFileIcon, tr("New File"));
    toolBar->addWidget(newFileButton);
    connect(newFileButton, SIGNAL(clicked(bool)), this, SLOT(addTab()));
    newFileButton->setToolTip(tr("Create new file"));

    /*SAVE*/
    saveButton = new QPushButton(*saveIcon, tr("Save"));
    toolBar->addWidget(saveButton);
    connect(saveButton, SIGNAL(clicked(bool)), this, SLOT(saveFile()));
    saveButton->setToolTip(tr("Save current file"));

    /* UNDO */
    undoButton = new QPushButton(*undoIcon, tr("Undo"));
    toolBar->addWidget(undoButton);
//    connect(undoButton, SIGNAL(clicked(bool)), editorTabs, SLOT(undo()));
    undoButton->setToolTip(tr("Undo"));

    compileButton = new QPushButton(*buildIcon, tr("Compile"));
    toolBar->addWidget(compileButton);
    compileButton->setToolTip(tr("Compile"));
//    compileButton->setStyleSheet("*{border: none;}");

    runButton = new QPushButton(*runIcon, tr("Run"));
    toolBar->addWidget(runButton);
    runButton->setToolTip(tr("Run"));
}

void MainWindow::createStatusBar()
{
//    QLabel *extensionLabel = new QLabel();
//    this->windowStatusBar->addWidget(extensionLabel);
}

void MainWindow::createActions()
{
    createFileActions();
    createEditActions();
    createCompileActions();
    createHelpActions();
}

void MainWindow::createFileActions()
{
    /* New Window Act */
    newWindowAct = new QAction(tr("&New Window"), this);
    newWindowAct->setShortcuts(QKeySequence::New);
    newWindowAct->setStatusTip(tr("Create a new window"));
//    connect(newWindowAct, SIGNAL(triggered(bool)), this, SLOT(newWindow()));

//    newTabAct = new QAction(*newTabIcon, tr("New &Tab"), this);
//    newTabAct->setShortcuts(QKeySequence::AddTab);
//    newTabAct->setStatusTip(tr("Create new tab"));
//    connect(newTabAct, SIGNAL(triggered(bool)), this, SLOT(addTab()));

    /* New File */
    newFileAct = new QAction(*newFileIcon, tr("New F&ile"), this);
    newFileAct->setStatusTip(tr("Create new File"));
    connect(newFileAct, SIGNAL(triggered(bool)), this, SLOT(addTab()));

    /* New Project */
    newProjectAct = new QAction(*newFileIcon, tr("New P&roject"), this);
    newProjectAct->setStatusTip("Create new cmake Project");
//    connect(newProjectAct, SIGNAL(triggered(bool)), this, SLOT(newProject()));

    /* Open File */
    openFileAct = new QAction(*openIcon, tr("&Open File"), this);
    openFileAct->setShortcut(QKeySequence::Open);
    openFileAct->setStatusTip(tr("Open existing File"));
    connect(openFileAct, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    /* Open Folder */
    openFolderAct = new QAction(*openIcon, tr("&Open Folder"), this);
    openFolderAct->setStatusTip(tr("Open existing Folder"));
    connect(openFolderAct, SIGNAL(triggered(bool)), this, SLOT(openFolder()));

    /* Save File */
    saveFileAct = new QAction(*saveIcon, tr("&Save"), this);
    saveFileAct->setShortcut(QKeySequence::Save);
    saveFileAct->setStatusTip(tr("Save a file"));
    connect(saveFileAct, SIGNAL(triggered(bool)), this, SLOT(saveFile()));

    /* Save As File */
    saveFileAsAct = new QAction(*saveAsIcon, tr("Save as"), this);
    saveFileAsAct->setShortcut(QKeySequence::SaveAs);
    saveFileAsAct->setStatusTip(tr("Save as file"));
    connect(saveFileAsAct, SIGNAL(triggered(bool)), this, SLOT(saveAsFile()));

    /* Exit Application */
    exitAct = new QAction(tr("Exit"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Close current window"));
    connect(exitAct, SIGNAL(triggered(bool)), this, SLOT(closeWindow()));
}


void MainWindow::createEditActions()
{
    // Editor *currentEditor = dynamic_cast<Editor*>(tab->currentWidget());

    undoAct = new QAction(*undoIcon, tr("Undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
//    connect(undoAct, SIGNAL(triggered(bool)), tab, SLOT(undo()));

    redoAct = new QAction(*redoIcon, tr("Redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
//    connect(redoAct, SIGNAL(triggered(bool)), tab, SLOT(redo()));

    copyAct = new QAction(*copyIcon, tr("Copy"), this);
    copyAct->setShortcut(QKeySequence::Copy);
//    connect(copyAct, SIGNAL(triggered(bool)), tab, SLOT(copy()));

    cutAct = new QAction(*cutIcon, tr("Cut"), this);
    cutAct->setShortcut(QKeySequence::Cut);
//    connect(cutAct, SIGNAL(triggered(bool)), tab, SLOT(cut()));

    pasteAct = new QAction(*pasteIcon, tr("Paste"), this);
    pasteAct->setShortcut(QKeySequence::Paste);
//    connect(pasteAct, SIGNAL(triggered(bool)), tab, SLOT(paste()));
}


void MainWindow::createCompileActions()
{
    compileAct = new QAction(tr("Compile"), this);

    buildAct = new QAction(tr("Build"), this);

    makeAct = new QAction(tr("Make"), this);

    runAct = new QAction(tr("Run"), this);

    buildSettingsAct = new QAction(tr("Build Settings"), this);
    buildSettingsAct->setStatusTip(tr("Open settings window"));
//    connect(buildSettingsAct, SIGNAL(triggered(bool)), this, SLOT(openSettingsWindow()));
}

void MainWindow::createHelpActions()
{
    aboutAct = new QAction(tr("About"), this);
    aboutQtAct = new QAction(tr("About Qt"), this);
}

void MainWindow::createTerminal()
{
    console = new QTermWidget();
    QFont font = QFont();
    font.setFamily("Monospace");
    font.setPointSize(12);
    console->setTerminalFont(font);
    console->setColorScheme("Solarized");
}

void MainWindow::newWindow()
{

}

void MainWindow::newFile()
{
    Editor *currentEditor = dynamic_cast<Editor*>(editorTabs->currentWidget());
    /* if current editor is not empty create new tab */
    if (!currentEditor->document()->toPlainText().isEmpty()) {
        this->addTab();
    }

}

void MainWindow::newProject()
{

}

void MainWindow::saveFile()
{
    /*cast current tab widget to Editor*/
    Editor *currentEditor = dynamic_cast<Editor*>(editorTabs->currentWidget());
    QString openedFileName = currentEditor->getOpenedFileName();

    if (openedFileName.isEmpty()) {
        this->saveAsFile();
    }
    else {
        QFile file(openedFileName);
        if (file.open(QIODevice::ReadWrite)) {
          QTextStream stream(&file);
                    stream << currentEditor->document()->toPlainText();
                    file.flush();
                    file.close();
                }
                else {
                    QMessageBox::critical(this, tr("Errore"), tr("Cant save file"));
                    return;
                }
    }


}

void MainWindow::saveAsFile()
{
    /* filename to be saved */
        QString filename = QFileDialog::getSaveFileName(this, tr("Save As File"), tr("All files(*)"));

        if(filename.isEmpty()) {
            return;
        }

        /* file object */
        QFile *file = new QFile(filename);
        try{
        // if file is not open
            if (!file->open(QIODevice::WriteOnly | QIODevice::Text)){
                QErrorMessage *fileError = new QErrorMessage();
                fileError->showMessage(tr("ERROR by saving"));
                return;
            }
            /* cast the curent tab to Editor */
            Editor *currentEditor = dynamic_cast<Editor*>(this->editorTabs->currentWidget());
            currentEditor->setFileNameAndExtension(filename);   /* editor filename and filetype setup */
            Highlighter *currentHighlighter = new Highlighter(currentEditor->document());
            currentHighlighter->setupRule(currentEditor->getFileExtension());

            QString info = ">> " + filename + " saved\n";
            qDebug() << info << "\n";
//            windowStatusBar->showMessage(currentEditor->getFileExtension());    /* show the file extension in the statusbar */
            windowStatusBar->setFileExtension(currentEditor->getFileExtension());

            file->write(currentEditor->toPlainText().toStdString().c_str()); /* write text to the file */
            file->flush();
            file->close();
            emit(currentEditor->filenameChanged(filename));
            editorTabs->setTabText(editorTabs->currentIndex(), currentEditor->getShortFileName());

        }
        catch(...){
            QErrorMessage *fileError = new QErrorMessage();
            fileError->showMessage(tr("ERROR by saving"));
            try{
                file->close();
            }
            catch(...){
                std::cout << "[SAVE AS:] file close error" << endl;
//                this->console->appendDebuginfo("[SAVE AS:] file close error");
            }
        }
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open File"), tr("All files(*)"));

        if(filename.isEmpty()){
            return;
        }
        else{
            QFile *file = new QFile(filename);

            try{
                addTab();
                if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
                    QErrorMessage *fileError = new QErrorMessage();
                    fileError->showMessage(tr("ERROR by opening file"));
                }

                /* cast QWidget to Editor */
                Editor *currentEditor = dynamic_cast<Editor*>(editorTabs->currentWidget());
                currentEditor->openFile(filename);

                emit(currentEditor->filenameChanged(filename));
                editorTabs->setTabText(editorTabs->currentIndex(), currentEditor->getShortFileName());
                windowStatusBar->setFileExtension(currentEditor->getFileExtension());

            }
            catch (...){
                std::cout << "error opening file" << std::endl;
//                console->appendDebuginfo("[OPENFILE]: error opening file");
                try {
                    file->close();
                }
                catch(...) {
                    std::cout << "[OPEN:] file close error" << std::endl;
//                    console->appendDebuginfo("[OPENFILE]: error closing file");
                }
            }
        }
}

void MainWindow::openFolder()
{
    QString home = QProcessEnvironment::systemEnvironment().value("HOME", "/");
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Folder"), home);

    if(dirPath.isEmpty()){
        return;
    }
    else {
        this->fileManager->setDir(dirPath);
    }
}

void MainWindow::openFile(QString path)
{
    if(path.isEmpty()){
            return;
        }
        else{
            QFile *file = new QFile(path);

            try{
                addTab();
                if (!file->open(QIODevice::ReadOnly | QIODevice::Text)){
                    QErrorMessage *fileError = new QErrorMessage();
                    fileError->showMessage(tr("ERROR by opening file"));
                }

                /* cast QWidget to Editor */
                Editor *currentEditor = dynamic_cast<Editor*>(editorTabs->currentWidget());
                currentEditor->openFile(path);

                emit(currentEditor->filenameChanged(path));
                editorTabs->setTabText(editorTabs->currentIndex(), currentEditor->getShortFileName());
                windowStatusBar->setFileExtension(currentEditor->getFileExtension());   // set file extension and show in statusbar

            }
            catch (...){
                std::cout << "error opening file" << std::endl;
//                console->appendDebuginfo("[OPENFILE]: error opening file");
                try {
                    file->close();
                }
                catch(...) {
                    std::cout << "[OPEN:] file close error" << std::endl;
//                    console->appendDebuginfo("[OPENFILE]: error closing file");
                }
            }
        }

}

void MainWindow::addTab()
{


    this->editorTabs->addTab(new Editor(), tr("New File"));
    int tabCount = this->editorTabs->count();
    qDebug() << tabCount;
    this->editorTabs->setCurrentIndex(tabCount - 1);
}

void MainWindow::saveGeometry()
{


}

void MainWindow::saveSettings()
{
    QSettings settings(QString("configs/config.ini"), QSettings::IniFormat);

    settings.setValue("window/geometry", this->geometry());
    settings.setValue("window/vertical_splitter", this->verticalSplitter->saveState());
    settings.setValue("window/horizontal_splitter", this->horizontalSplitter->saveState());
    settings.setValue("theme", "default.css");

    QStringList openedFiles;
    for(int i = 0; i < editorTabs->count(); i++) {
        editorTabs->setCurrentIndex(i);
        Editor *currentEditor = dynamic_cast<Editor*>(editorTabs->currentWidget());
        openedFiles.append(currentEditor->getOpenedFileName());
    }

    settings.setValue("openedfiles", openedFiles);


    settings.setValue("openedfolder", fileManager->getCurrentDirecotry());

}

/**
 * @brief MainWindow::loadSettings
 * save settings when closing window
 * window geometry
 * splitter states
 * opened files name
 * and the filemanagers current direcotry
 */
void MainWindow::loadSettings()
{
    if(QFile::exists(QString("configs/config.ini"))) {

        QSettings settings(QString("configs/config.ini"), QSettings::IniFormat);

        QRect geometry =  settings.value("window/geometry", this->geometry()).toRect();
        this->setGeometry(geometry);

        QByteArray state = settings.value("window/vertical_splitter").toByteArray();
        this->verticalSplitter->restoreState(state);
        state = settings.value("window/horizontal_splitter").toByteArray();
        this->horizontalSplitter->restoreState(state);
//        settings.setValue("theme", "default.css");

        try {
            QStringList openedFiles = settings.value("openedfiles").toStringList();

            for(int i = 0; i < openedFiles.length(); i++){
                openFile(openedFiles.at(i));
            }
        } catch(...) {
            qDebug() << "Couldnt open last session\n";
        }
        fileManager->setDir(settings.value("openedfolder").toString());
    }
}


void MainWindow::openSettingsWindow()
{

}

void MainWindow::saveLastSession()
{

}

void MainWindow::undo()
{

}

void MainWindow::redo()
{

}

// TODO:
void MainWindow::updateStatusbar(int)
{
    Editor *newEditor = dynamic_cast<Editor*>(this->editorTabs->currentWidget());

    QString fileExtension = newEditor->getFileExtension();
    windowStatusBar->setFileExtension(fileExtension);

}

void MainWindow::closeTab(int index)
{
    std::cout << "close Tab clicked" << index << std::endl;
    int currentIndex = this->editorTabs->currentIndex();
    if (index <= currentIndex ) {
        currentIndex -= 1;
    }
    this->editorTabs->removeTab(index);
    this->editorTabs->setCurrentIndex(currentIndex);

}

void MainWindow::closeEvent(QCloseEvent *event)
{

    this->closeWindow();

}

void MainWindow::closeWindow()
{
    qDebug() << "Exit\n";
    this->saveSettings();
    this->close();
}

