#ifndef WEIGHTFILTER_GLOBAL_H
#define WEIGHTFILTER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WEIGHTFILTER_LIBRARY)
#  define WEIGHTFILTERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define WEIGHTFILTERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WEIGHTFILTER_GLOBAL_H
