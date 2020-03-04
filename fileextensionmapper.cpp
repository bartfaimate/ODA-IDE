#include "fileextensionmapper.h"

FileExtensionMapper* FileExtensionMapper::onlyInstance = nullptr;

FileExtensionMapper::FileExtensionMapper()
{
    /* C types */
    this->extensionToTypeMap[QString(".c")] = FileTypes::C_SOURCE;
    this->extensionToTypeMap[QString(".h")] = FileTypes::C_HEADER;

    /* CPP types */
    this->extensionToTypeMap[QString(".cpp")] = FileTypes::CPP_SOURCE;
    this->extensionToTypeMap[QString(".cxx")] = FileTypes::CPP_SOURCE;
    this->extensionToTypeMap[QString(".cc")] = FileTypes::CPP_SOURCE;

    this->extensionToTypeMap[QString(".hpp")] = FileTypes::CPP_HEADER;
    this->extensionToTypeMap[QString(".hxx")] = FileTypes::CPP_HEADER;
    this->extensionToTypeMap[QString(".hh")] = FileTypes::CPP_HEADER;

    /* JAVA types */
    this->extensionToTypeMap[QString(".java")] = FileTypes::JAVA_SOURCE;

    /* PYTHON types*/
    this->extensionToTypeMap[QString(".py")] = FileTypes::PYTHON_SOURCE;

    /* JAVASCRIPT types*/
    this->extensionToTypeMap[QString(".js")] = FileTypes::JAVASCRIPT_FILE;

    /* HTML types */
    this->extensionToTypeMap[QString(".htm")] = FileTypes::HTML_FILE;
    this->extensionToTypeMap[QString(".html")] = FileTypes::HTML_FILE;
    this->extensionToTypeMap[QString(".dhtml")] = FileTypes::HTML_FILE;
    this->extensionToTypeMap[QString(".dochtml")] = FileTypes::HTML_FILE;

    /* CSS Types */
    this->extensionToTypeMap[QString(".css")] = FileTypes::CSS_FILE;

    /* JSON Types */
    this->extensionToTypeMap[QString(".json")] = FileTypes::JSON_FILE;

    /* Makefiles */
    this->extensionToTypeMap[QString(".mk")] = FileTypes::MAKEFILE;
    this->extensionToTypeMap[QString(".makefile")] = FileTypes::JSON_FILE;

    /* Text files */
    this->extensionToTypeMap[QString(".txt")] = FileTypes::TEXT_FILE;


    this->typeToStringMap[FileTypes::C_HEADER] =        QString("C header");
    this->typeToStringMap[FileTypes::C_SOURCE] =        QString("C source");
    this->typeToStringMap[FileTypes::CPP_HEADER] =      QString("C++ header");
    this->typeToStringMap[FileTypes::CPP_SOURCE] =      QString("C++ source");
    this->typeToStringMap[FileTypes::JAVA_SOURCE] =     QString("Java source");
    this->typeToStringMap[FileTypes::PYTHON_SOURCE] =   QString("Python source");
    this->typeToStringMap[FileTypes::HTML_FILE] =       QString("HTML");
    this->typeToStringMap[FileTypes::JAVASCRIPT_FILE] = QString("JavaScript");
    this->typeToStringMap[FileTypes::MAKEFILE] =        QString("Makefile");
    this->typeToStringMap[FileTypes::CSS_FILE] =        QString("CSS Stylesheet");
    this->typeToStringMap[FileTypes::TEXT_FILE] =       QString("Text");
    this->typeToStringMap[FileTypes::JSON_FILE] =       QString("JSon");
    this->typeToStringMap[FileTypes::OTHER] =           QString("plain");

}

FileExtensionMapper *FileExtensionMapper::getInstance()
{
    if(onlyInstance == nullptr) {
        onlyInstance = new FileExtensionMapper();
    }

    return onlyInstance;
}

FileTypes FileExtensionMapper::extensionToType(QString extension)
{
    FileTypes type = this->extensionToTypeMap.value(extension, FileTypes::OTHER);
    return type;
}

QString FileExtensionMapper::typeToString(FileTypes fileType)
{
    QString language = this->typeToStringMap.value(fileType, "text");
    return language;
}

QString FileExtensionMapper::extensionToString(QString extension)
{
    FileTypes type =  this->extensionToType(extension);
    QString str = this->typeToString(type);
    return str;
}

