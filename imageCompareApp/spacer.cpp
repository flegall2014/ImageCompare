#include "spacer.h"

// Constructor:
Spacer::Spacer(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

// Destructor:
Spacer::~Spacer()
{

}

