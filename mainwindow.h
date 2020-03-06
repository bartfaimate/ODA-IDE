#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMainWindow>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSplitter>
#include <QDebug>
#include <QSettings>
#include <QErrorMessage>
#include <QFileDialog>
#include <QMutex>

//#include "tab.h"
#include "editor.h"
#include "statusbar.h"
#include "filemanager.h"
//#include "terminal.h"
#include "fileextensionmapper.h"
#include "qtermwidget5/qtermwidget.h"


using namespace odaide;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QTabWidget *editorTabs;
    QTabWidget *outputTabs;

    QString companyName = "OI";
    QString appName = "ODA-IDE";
    QString title = tr("ODA-IDE");
    QString iconPath = "./icons/1x/";

    QString configFolder = "configs/";
    QString baseFolder;
    QString configFile = "config.ini";

    QString settingsPath = "configs/settings.ini";

    QList<QString> *openedFiles;

    QHBoxLayout *hBoxLayout;
    QSplitter *verticalSplitter;
    QSplitter *horizontalSplitter;
    QMenuBar *menuBar;
    QToolBar *toolBar;

    /* toolbar buttons */
    QPushButton *newFileButton;
    QPushButton *newTabButton;
    QPushButton *saveButton;
    QPushButton *undoButton;
    QPushButton *newWindowButton;
    QPushButton *compileButton;
    QPushButton *runButton;

    StatusBar *windowStatusBar;

    /* icons */
    QIcon *newTabIcon = new QIcon(iconPath + "baseline_add_black_48dp.png");
    QIcon *newFileIcon = new QIcon(iconPath + "baseline_insert_drive_file_black_48dp.png");
    QIcon *saveIcon = new QIcon(iconPath + "baseline_save_black_48dp.png");
    QIcon *saveAsIcon = new QIcon(iconPath + "baseline_save_alt_black_48dp.png");
    QIcon *openIcon = new QIcon("./img/gnome-icons/document-open.svg");

    QIcon *buildIcon = new QIcon(iconPath + "baseline_build_black_48dp.png");
    QIcon *runIcon = new QIcon(iconPath + "baseline_play_arrow_black_48dp.png");

    QIcon *undoIcon = new QIcon(iconPath + "baseline_undo_black_48dp.png");
    QIcon *redoIcon = new QIcon(iconPath + "baseline_redo_black_48dp.png");
    QIcon *copyIcon = new QIcon("./img/gnome-icons/edit-copy.png");
    QIcon *pasteIcon = new QIcon("./img/gnome-icons/edit-paste.png");
    QIcon *cutIcon = new QIcon("./img/gnome-icons/edit-cut.png");

    /* menus */
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QMenu *compilerMenu;
    /*file menu*/
    QAction *newWindowAct;
    QAction *newTabAct;
    QAction *newFileAct;
    QAction *newProjectAct;
    QAction *openFileAct;
    QAction *openFolderAct;
    QAction *saveFileAct;
    QAction *saveFileAsAct;
    QAction *printAct;
    QAction *exitAct;
    /*edit menu*/
    QAction *undoAct;
    QAction *redoAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    /*compiler menu*/
    QAction *compileAct;
    QAction *buildAct;
    QAction *makeAct;
    QAction *buildSettingsAct;
    QAction *runAct;
    /*help menu*/
    QAction *aboutAct;
    QAction *aboutQtAct;

    QMutex currentEditorLock;      /* this is a mutex for currentEditor. If it would be changed this lock must be set*/

    MainWindow *newWindows;

    QMutex tabLock;
    QMutex settingsLock;


    FileManager *fileManager;
    FileExtensionMapper *mapper;

    QTermWidget *console;

    Editor *currentEditor;

    QMap<QString, QString> fileTypeMapper;

//    odaide::TerminalThread *consoleThread;

private:
    void createLayout();
    void createMenus();
    void createFileMenu();
    void createEditMenu();
    void createCompileMenu();
    void createHelpMenu();
    void createButtons();

    void createStatusBar();

//    void setupTabs();

    void createActions();
    void createFileActions();
    void createEditActions();
    void createCompileActions();
    void createHelpActions();
    void createFileMapper();
    void createTerminal();

//    void createStatusbar(int height);

    void keyPressEvent(QKeyEvent *event);

public slots:
    void newWindow();
    void newFile();
    void newProject();
    void saveFile();
    void saveAsFile();
    void openFile();
    void openFolder();
    void openFile(QString path);
    void addTab();
    void saveGeometry();
    void saveSettings();
    void loadSettings();
    void openSettingsWindow();

    void saveLastSession();
    void setCurrentEditor();
    void setCurrentEditor(int index);
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();

    void updateStatusbar(int);

    void closeTab(int index);
    void closeWindow();

    void about();
    void aboutQt();


//    void updateSettings();
public:
     virtual void closeEvent ( QCloseEvent * event );
};

#endif // MAINWINDOW_H
