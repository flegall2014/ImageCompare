#ifndef DEFS_H
#define DEFS_H

#define UNKNOWN_PICTO "qrc:/qml/icons/ico-missing.png"
#define BLUE_FOLDER_PICTO ":/qml/icons/ico-bluefolder.png"
#define GREEN_FOLDER_PICTO ":/qml/icons/ico-greenfolder.png"
#define RED_FOLDER_PICTO ":/qml/icons/ico-redfolder.png"

// Match structure:
typedef struct MatchStruct {
    QString _qmlFile;
    uint _lineNumber;
    QString _line;
    QString _searchedString;
} MatchStruct;

// Hunt role:
enum HuntRole {
    QMLFileRole=Qt::UserRole+1,
    LineNumberRole,
    LineRole
};

#endif // DEFS_H
