#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QMainWindow>
#include <QtWidgets>
#include <QTextCodec>

class TextEdit;
class TextEditor : public QMainWindow
{
    Q_OBJECT

public:
    TextEditor();
    ~TextEditor();
    static TextEditor* getInstance();
    void loadFile(const QString &fileName);
    void setText(QString value);
    void setFontPointSize(int value);
    QString getCurrentDirectory() const;
    void setCurrentDirectory(const QString &value);
    void searchText(const QString &text);
    QString getTitle() const;
    void clear();
    void setTitle(const QString &title);

protected:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void newFile();
    void open();
    void grapLink();
    bool save();
    bool saveAs();
    void about();
    void documentWasModified();
    void search();
    void searchText();
    void sltToggleComment();
    void sltCopyLineDown();
    void sltSearchTextChanged(QString key);
signals:
    void sgnFileChanged();
    void sgnQmlfileClosed();
    void sgnGrapText(QString value);
private:
    QString currentDirectory;
    void createActions();
    void createMenus();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QToolBar *toolbar;
    TextEdit *textEdit;
    QString curFile;
    QString textToSearch;
    bool visibility;
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exitAct;
    QAction *cutAct;
    QAction *copyAct;
    QAction *pasteAct;
    QAction *aboutAct;
    QAction *searchAct;
    QAction *getlink;
    QAction *toggleComment;
    QAction *copyLineDown;
    QFile *file;
    QLineEdit* searchLineEdit;
    QAbstractItemModel *modelFromFile(const QString& fileName);
    QCompleter *completer;
    QString m_title;
};

#endif
