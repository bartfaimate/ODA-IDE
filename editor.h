#ifndef EDITOR_H
#define EDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QString>
#include <QCompleter>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
class QCompleter;
QT_END_NAMESPACE

class LineNumberArea;

//![codeeditordefinition]

class Editor : public QPlainTextEdit
{
    Q_OBJECT

public:
    Editor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();
    void setFontSettings();
    void setFontSettings(QString fontFamily, int fontSize, int tabWidth);
    void setFontSettings(QString fontFaimily, int tabwidth);
    void setFileExtension();
    void setOpenedFileName(QString openedFilename);
    void setFileNameAndExtension(QString openedFileName);
    QString getFileExtension();
    QString getOpenedFileName();
    QString getShortFileName();

    void setCompleter(QCompleter *c);
    QCompleter *completer() const;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *e) override;



private slots:

    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void highlightCurrentLine(QString highlightColor, int lighten);
    void highlightCurrentLineWrapper();
    void updateLineNumberArea(const QRect &, int);
    int getLineIndent();
    int getLineIndent(int row);
    long int lineCount();

public slots:
    void openFile(QString fileName);
    void saveFile(QString fileName);
    void newFile(QString fileName);

signals:
    void filenameChanged(QString);


private:
    QWidget *lineNumberArea;
    QFont *font;
    QFontMetrics *metrics;
    QString openedFileName;
    QString fileExtension;
    QString highlightColor;
    QString fontFamily;
    int tabWidth;
    int fontSize;
    int lightenValue;




public:
    int getLightenValue();
    void setLightenValue(int lighten);
    QString getHighlightColor();
    void setHighlightColor(QString color);
    void setFontFamily(QString fontFamily);
    QString getFontFamily();
    void setTabWidth(int tabWidth);
    int getTabWidth();
    void setFontSize(int fontSize);
    int getFontSize();
};

//![codeeditordefinition]
//![extraarea]

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(Editor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(codeEditor->lineNumberAreaWidth(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);
    }

private:
    Editor *codeEditor;
};

//![extraarea]

#endif // EDITOR_H
