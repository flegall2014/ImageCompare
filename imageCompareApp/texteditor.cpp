#include "textEditor.h"
#include "textedit.h"

TextEditor *TextEditor::getInstance()
{
    static TextEditor* instance(new TextEditor());
    return instance;
}

TextEditor::TextEditor():
    completer(0)

{
    textEdit = new TextEdit;
    completer = new QCompleter(this);
    visibility = false;
    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText("search");
    completer->setModel(modelFromFile(":/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);
    textEdit->setCompleter(completer);

    setCentralWidget(textEdit);
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();

    readSettings();

    connect(textEdit->document(), SIGNAL(contentsChanged()),
            this, SLOT(documentWasModified()));
    connect(searchLineEdit, SIGNAL(textChanged(QString)),
            this, SLOT(sltSearchTextChanged(QString)));
    connect(searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(searchText()));

    setCurrentFile("");
    setUnifiedTitleAndToolBarOnMac(true);
}

TextEditor::~TextEditor()
{
    delete fileMenu;
    delete editMenu;
    delete helpMenu;
    delete searchLineEdit;
    delete textEdit;
    delete fileToolBar;
    delete editToolBar;
    delete toolbar;
    delete completer;
    delete newAct;
    delete openAct;
    delete saveAct;
    delete saveAsAct;
    delete exitAct;
    delete cutAct;
    delete copyAct;
    delete getlink;
    delete pasteAct;
    delete aboutAct;
    delete searchAct;
    delete toggleComment;
    delete copyLineDown;
   // delete file;
}


void TextEditor::closeEvent(QCloseEvent *event)

{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
    file->close();
    sgnQmlfileClosed();
}

void TextEditor::newFile()
{
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFile("");
    }

}

void TextEditor::open()
{
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,"save a file",currentDirectory);
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

void TextEditor::grapLink()
{
    QString text =textEdit->textCursor().block().text().trimmed() ;
    QString value =text.replace("{","");
    sgnGrapText(value.replace(" ",""));
}

void TextEditor::sltToggleComment()
{
    int currentLine = textEdit->textCursor().blockNumber() + 1;

    QString text = textEdit->textCursor().block().text().trimmed() ;

    QTextCursor cursor(textEdit->document()->findBlockByLineNumber(currentLine-1)); // ln-1 because line number starts from 0
    textEdit->setTextCursor(cursor);

    if(!text.contains("//"))
    {
        textEdit->insertPlainText("//");
    }
    else
    {
        cursor.select(QTextCursor::BlockUnderCursor);
        cursor.removeSelectedText();
        if(currentLine != 1)
            textEdit->insertPlainText("\n");
        textEdit->insertPlainText(text.replace("//",""));
    }
}

void TextEditor::sltCopyLineDown()
{
    int currentLine = textEdit->textCursor().blockNumber() + 1;

    QString text = textEdit->textCursor().block().text().trimmed() ;

    QTextCursor cursor(textEdit->document()->findBlockByLineNumber(currentLine-1)); // ln-1 because line number starts from 0
    textEdit->setTextCursor(cursor);
    textEdit->insertPlainText(text + "\n");
}

bool TextEditor::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool TextEditor::saveAs()
{
    QFileDialog dialog(this,"save As",currentDirectory,tr("qml(*.qml);;JS files (*.js);;ts files (*.ts);;Text files (*.txt);;All files (*.*)"));
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setDefaultSuffix("qml");
    dialog.selectFile(curFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList files;
    if (dialog.exec())
        files = dialog.selectedFiles();
    else
        return false;

    return saveFile(files.at(0));
}

void TextEditor::about()
{
    QMessageBox::about(this, tr("About Application"),
                       tr("This application is a custom text Editor"));
}

void TextEditor::documentWasModified()
{
    setWindowModified(textEdit->document()->isModified());
}

void TextEditor::search()
{
    visibility = !visibility;
    searchLineEdit->setText(textEdit->textCursor().selectedText());
    toolbar->setVisible(visibility);
}

void TextEditor::searchText(const QString &textToSearch)
{
    textEdit->findText(textToSearch);
}

void TextEditor::searchText()
{
    textEdit->findText(textToSearch);
}

void TextEditor::sltSearchTextChanged(QString key)
{
    textToSearch = key;
}

QString TextEditor::getCurrentDirectory() const
{
    return currentDirectory;
}

void TextEditor::setCurrentDirectory(const QString &value)
{
    currentDirectory = value;
}

void TextEditor::createActions()

{
    newAct = new QAction(QIcon(":/qml/icons/resourcefilter/new.png"), tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Create a new file"));
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/qml/icons/resourcefilter/open.png"), tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    getlink = new QAction(QIcon(":/qml/icons/resourcefilter/hand.png"), tr("&GoToLink"), this);
    getlink->setStatusTip(tr("Go to the focused Qml Object (F2)"));
//    getlink->setShortcutContext(Qt::WidgetWithChildrenShortcut);
    getlink->setShortcut(QKeySequence ("F2"));
    toggleComment = new QAction(QIcon(":/qml/icons/resourcefilter/commentIcon.png"), tr("&ToggleComment"), this);
    toggleComment->setStatusTip(tr("toggle Comment "));
    toggleComment->setShortcut(QKeySequence ("ctrl+:"));
    copyLineDown = new QAction(QIcon(":/qml/icons/resourcefilter/linedown.svg"), tr("&copyLineDown"), this);
    copyLineDown->setStatusTip(tr("copy line down "));
    copyLineDown->setShortcut(QKeySequence ("ctrl+D"));
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
    connect(getlink, SIGNAL(triggered()), this, SLOT(grapLink()));
    connect(toggleComment, SIGNAL(triggered()), this, SLOT(sltToggleComment()));
    connect(copyLineDown, SIGNAL(triggered()), this, SLOT(sltCopyLineDown()));

    saveAct = new QAction(QIcon(":/qml/icons/resourcefilter/save.png"), tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the document to disk"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(QIcon(":/qml/icons/resourcefilter/save_as.png"),tr("Save &As..."), this);
    saveAsAct->setShortcut(QKeySequence("ctrl+alt+s"));
    saveAsAct->setStatusTip(tr("Save the document under a new name"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exitAct = new QAction(QIcon(":/qml/icons/resourcefilter/fileclose.png"),tr("&Exit"), this);
    exitAct->setShortcut(QKeySequence ("ctrl+q"));

    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    cutAct = new QAction(QIcon(":/qml/icons/resourcefilter/cut.png"), tr("&Cut"), this);

    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tr("Cut the current selection's contents to the "
                            "clipboard"));
    connect(cutAct, SIGNAL(triggered()), textEdit, SLOT(cut()));

    copyAct = new QAction(QIcon(":/qml/icons/resourcefilter/copy.png"), tr("&Copy"), this);
    copyAct->setShortcuts(QKeySequence::Copy);
    copyAct->setStatusTip(tr("Copy the current selection's contents to the "
                             "clipboard"));
    connect(copyAct, SIGNAL(triggered()), textEdit, SLOT(copy()));

    pasteAct = new QAction(QIcon(":/qml/icons/resourcefilter/paste.png"), tr("&Paste"), this);
    pasteAct->setShortcuts(QKeySequence::Paste);
    pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
                              "selection"));
    connect(pasteAct, SIGNAL(triggered()), textEdit, SLOT(paste()));

    aboutAct = new QAction(QIcon(":/qml/icons/resourcefilter/Info.png"),tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    aboutAct->setShortcut(QKeySequence("ctrl+h"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    searchAct = new QAction(QIcon(":/qml/icons/resourcefilter/search-icon.png"),tr("&search..."), this);
    searchAct->setShortcuts(QKeySequence::Find);
    searchAct->setStatusTip(tr("search for a text"));
    connect(searchAct, SIGNAL(triggered()), this, SLOT(search()));

    cutAct->setEnabled(false);

    copyAct->setEnabled(false);
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            cutAct, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)),
            copyAct, SLOT(setEnabled(bool)));
}

void TextEditor::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addAction(searchAct);
    editMenu->addAction(toggleComment);
    editMenu->addAction(copyLineDown);
    editMenu->addAction(getlink);
    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void TextEditor::createToolBars()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(newAct);

    fileToolBar->addAction(openAct);

    fileToolBar->addAction(saveAct);

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addAction(getlink);

    addToolBarBreak();
    toolbar = addToolBar("toolbar");
    toolbar->addWidget(searchLineEdit);
    toolbar->setVisible(visibility);

}


void TextEditor::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));
}


void TextEditor::readSettings()
{
    QSettings settings("QtProject", "Application Example");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}


void TextEditor::writeSettings()
{
    QSettings settings("QtProject", "Application Example");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}


bool TextEditor::maybeSave()
{
    if (textEdit->document()->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("Application"),
                                   tr("The document has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}


void TextEditor::loadFile(const QString &fileName)
{
    file = new QFile(fileName);
    if (!file->open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file->errorString()));
        return;
    }
    qDebug()<<"file RW permission set to:  "<< file->setPermissions(QFile::WriteUser | QFile::ReadUser | QFile::WriteOwner | QFile::ReadOwner);

    QTextStream in(file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    textEdit->setFont(QFont("Arial",12));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QString str = in.readAll();
    textEdit->setPlainText(str);
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

void TextEditor::setText(QString value)
{
    textEdit->insertPlainText(value);
}

void TextEditor::setFontPointSize(int value)
{
    textEdit->setFont(QFont("Arial",value));
}


bool TextEditor::saveFile(const QString &fileName)
{
    QFile *file = new QFile(fileName);
    if (!file->open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file->errorString()));
        return false;
    }

    QTextStream out(file);
#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(Qt::WaitCursor);
#endif
    out << textEdit->toPlainText();
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);

    file->close();
    delete file;
    sgnFileChanged();
    return true;
}

void TextEditor::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
    m_title = shownName;
}

QString TextEditor::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

QAbstractItemModel *TextEditor::modelFromFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;


    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }

#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    qSort(words.begin(), words.end());

    return new QStringListModel(words, completer);
}
QString TextEditor::getTitle() const
{
    return m_title;
}

void TextEditor::clear()
{
    textEdit->clear();
}

void TextEditor::setTitle(const QString &title)
{
    m_title = title;
    QMainWindow::setWindowTitle(title);
}

