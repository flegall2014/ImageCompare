#ifndef SPACER_H
#define SPACER_H
#include <QWidget>

class Spacer : public QWidget
{
    Q_OBJECT

public:
    // Constructor:
    explicit Spacer(QWidget *parent = 0);

    // Destructor:
    virtual ~Spacer();

signals:

public slots:
};

#endif // SPACER_H
