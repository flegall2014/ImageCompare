#ifndef OKFILTER_GLOBAL_H
#define OKFILTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(OKFILTER_LIBRARY)
#  define OKFILTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define OKFILTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // OKFILTER_GLOBAL_H
