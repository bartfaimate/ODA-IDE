#ifndef FILEEXTENSIONMAPPER_H
#define FILEEXTENSIONMAPPER_H


#include <QMap>
#include <QString>
#include <QObject>

enum FileTypes{
    C_SOURCE,
    C_HEADER,
    CPP_SOURCE,
    CPP_HEADER,
    PYTHON_SOURCE,
    JAVA_SOURCE,
    MAKEFILE,
    CMAKELISTS,
    TEXT_FILE,
    JSON_FILE,
    HTML_FILE,
    JAVASCRIPT_FILE,
    CSS_FILE,
    OTHER
};


/**
  * This class should be a singleton class
  */
class FileExtensionMapper
{
private:
    static FileExtensionMapper *onlyInstance;
    QMap<FileTypes, QString> typeToStringMap;
    QMap<QString, FileTypes> extensionToTypeMap;

private:
    FileExtensionMapper();

public:
    static FileExtensionMapper* getInstance();

    FileTypes extensionToType(QString extension);
    QString typeToString(FileTypes fileType);
    QString extensionToString(QString extension);


};

#endif // FILEEXTENSIONMAPPER_H
