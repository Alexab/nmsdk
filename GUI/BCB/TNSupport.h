#ifndef TNSupportH
#define TNSupportH

#include "nmsdk_cpp_initdll.h"
#include "UWatchFrameUnit.h"

namespace NMSDK {

// Добавляем объект в окно наблюдений (график по времени)
void AddWatch(TUWatchFrame *watch, RDK::UContainer *item, int output, int outindex, double watchinterval, double yshift=0, TPenStyle style=psSolid, TColor color=TColor(0));

// Добавляем посторонний объект в окно наблюдений (график по времени)
void AddWatch(TUWatchFrame *watch, NameT name, double *y, double watchinterval, double yshift=0, TPenStyle style=psSolid, TColor color=TColor(0));

// Добавляем объект в окно наблюдений (график по частоте)
void AddFrequencyWatch(TUWatchFrame *watch, RDK::UContainer* item, double watchinterval, double yshift=0, TPenStyle style=psSolid, TColor color=TColor(0));

}
#endif
