#ifndef LARGEFILTER_GLOBAL_H
#define LARGEFILTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LARGEFILTER_LIBRARY)
#  define LARGEFILTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LARGEFILTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LARGEFILTER_GLOBAL_H
