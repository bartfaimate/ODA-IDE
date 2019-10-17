#include "filemanager.h"
#include <iostream>

FileManager::FileManager(QWidget *parent) : QTreeView (parent)
{
    model = new QFileSystemModel(this);

    QString home = QProcessEnvironment::systemEnvironment().value("HOME", "/");
//    model->setRootPath( home);
    this->setModel(model);
    this->setRootIndex(model->setRootPath(home));
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

/**
 * @brief FileManager::pathEmitter emits a signal if doubleclicked the model element and it is a file
 * @param index
 */
void FileManager::pathEmitter(const QModelIndex &index)
{
    QString path = model->filePath(index);
    if (fileExist(path)) {
        emit filePath(model->filePath(index));
    }
}

void FileManager::printPath(const QModelIndex &index)
{
    qDebug() << model->filePath(index) << "\n";

}

void FileManager::setDir(QString dirPath)
{
    this->setRootIndex(model->setRootPath(dirPath));
}
