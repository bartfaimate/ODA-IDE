#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QFileIconProvider>
#include <QDebug>
#include <QFileInfo>
#include <QProcessEnvironment>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QMouseEvent>
#include <QAbstractItemView>

class FileManager : public QTreeView
{
    Q_OBJECT
public:
    explicit FileManager(QWidget *parent = nullptr);

    ~FileManager();

    bool fileExist(QString path);
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    QString getCurrentDirecotry();
    void setCurrentDirecotry(QString dir);


signals:
    void signalFilePath(QString);

public slots:
    void pathEmitter(const QModelIndex & index);
    void printPath(const QModelIndex &index);
    void setDir(QString dirPath);

    bool createNewFile(QModelIndex &index);
    void renameFile();

private:
    QFileSystemModel *model;
    QModelIndex index;
    QAction *newFileAct;
    QAction *newFolderAct;
    QAction *newRenameAct;
    QAction *removeAct;

    QString currentDirectory;


    void createActions();
};

#endif // FILEMANAGER_H
