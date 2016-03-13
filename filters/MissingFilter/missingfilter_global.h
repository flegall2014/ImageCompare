#ifndef MISSINGFILTER_GLOBAL_H
#define MISSINGFILTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MISSINGFILTER_LIBRARY)
#  define MISSINGFILTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MISSINGFILTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MISSINGFILTER_GLOBAL_H