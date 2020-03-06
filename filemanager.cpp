#include "filemanager.h"
#include <iostream>

FileManager::FileManager(QWidget *parent) : QTreeView (parent)
{
    model = new QFileSystemModel(this);

    QString home = QProcessEnvironment::systemEnvironment().value("HOME", "/");
//    model->setRootPath( home);
    this->setSortingEnabled(true);
    this->setModel(model);
    this->setRootIndex(model->setRootPath(home));

    this->setCurrentDirecotry(home);

    /* sort by name */
    model->setFilter(QDir::AllDirs | QDir::AllEntries |QDir::NoDotAndDotDot );

    qDebug() << "[INFO]: rootpath" << this->model->rootPath();
    model->sort(0, Qt::SortOrder::AscendingOrder);

    // Demonstrating look and feel features
    this->setAnimated(false);
    this->setSortingEnabled(true);
    this->setIndentation(10);

    this->hideColumn(1);
    this->hideColumn(2);
    this->hideColumn(3);

    createActions();
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(printPath(QModelIndex)));
    connect(this, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(pathEmitter(QModelIndex)));
}

FileManager::~FileManager()
{
    delete model;
}

/**
 * @brief FileManager::fileExist checks if the file with the given path exists and the path is a file
 * @param path
 * @return true if the given path is a file
 */
bool FileManager::fileExist(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}

void FileManager::mouseReleaseEvent(QMouseEvent *event)
{
//    if (event->button() == Qt::RightButton) {

//            if (NULL != this->childAt(event->pos()) ) {
//                QMenu m;
//                m.addAction("Create File");
//                m.addAction("Create Folder");
//                m.addAction("Delete");


//                QAction *selected = m.exec(mapToGlobal(event->pos()));
//                if (selected) {

//                    qDebug() << "selected" << selected->text() << event->pos();
//                }
//            }
//        } else {
//            QTreeView::mouseReleaseEvent(event);
//    }
}

void FileManager::mousePressEvent(QMouseEvent *event)
{

    index = this->indexAt(event->pos());
    if (event->button() == Qt::LeftButton) {

        QTreeView::mousePressEvent(event);

    }
    if (event->button() == Qt::RightButton) {

            qDebug() << "Row" << index.row() << index.column();
            qDebug() << model->fileName(index);
            if (NULL != this->childAt(event->pos()) ) {
                QMenu m;
                m.addAction(newFileAct);
                m.addAction(newFolderAct);
                m.addAction(newRenameAct);
                if(model->isDir(index)) {
                    m.addAction("Delete folder");
                } else {
                    m.addAction("Delete file");
                }


                QAction *selected = m.exec(mapToGlobal(event->pos()));
                if (selected) {

                    qDebug() << "selected" << selected->text() << event->pos();
                }
            }
        }
    else {
            QTreeView::mouseReleaseEvent(event);
    }

}

QString FileManager::getCurrentDirecotry()
{
    return this->currentDirectory;
}

void FileManager::setCurrentDirecotry(QString dir)
{
    this->currentDirectory = dir;
}

/**
 * @brief FileManager::pathEmitter emits a signal if doubleclicked the model element and it is a file
 * @param index
 */
void FileManager::pathEmitter(const QModelIndex &index)
{
    QString path = model->filePath(index);
    if (fileExist(path)) {
        emit signalFilePath(model->filePath(index));
    }
}

void FileManager::printPath(const QModelIndex &index)
{
    qDebug() << model->filePath(index) << "\n";

}

void FileManager::setDir(QString dirPath)
{
    this->setRootIndex(model->setRootPath(dirPath));
    this->currentDirectory = dirPath;
}

bool FileManager::createNewFile(QModelIndex &index)
{

}

void FileManager::renameFile()
{

}

void FileManager::createActions()
{
    newFileAct = new QAction(tr("New F&ile"), this);
//    newFileAct->setStatusTip(tr("Create new File"));
//    connect(newFileAct, SIGNAL(triggered(bool)), this, SLOT());

    newFolderAct = new QAction("New folder");
    newRenameAct = new QAction("Rename");
    connect(newRenameAct, SIGNAL(triggered(bool)), this, SLOT(renameFile()));

    removeAct = new QAction();
}



