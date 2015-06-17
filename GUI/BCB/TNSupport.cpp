#ifndef TNSUPPORT_CPP
#define TNSUPPORT_CPP


#include "TNSupport.h"
#include "../Libraries/ReceiverLib/NReceiverLibrary.h"


namespace NMSDK {

// Добавляем объект в окно наблюдений (график по времени)
void AddWatch(TUWatchFrame *watch, RDK::UContainer *item, int output, int outindex, double watchinterval, double yshift, TPenStyle style, TColor color)
{
 UADItem *itemd=dynamic_cast<UADItem*>(item);

 if(!watch || !itemd)
  return;

 TUWatchInfo wd;
 wd.FullUpdate=false;
 wd.WatchInterval=watchinterval;
// wd.X=&UContainer::GetDoubleTime();

 wd.YShift=yshift;
 if(itemd->GetOwner())
  itemd->GetLongName(static_pointer_cast<UContainer>(itemd->GetOwner()->GetOwner()),wd.Legend);
 else
  itemd->GetLongName(0,wd.Legend);
 wd.Legend+=string("[")+RDK::sntoa(output)+string(":");
 wd.Legend+=RDK::sntoa(outindex)+string("]");
// wd.DataSource=item;

 if(color == 0) // Подбор подходящего цвета
  wd.Color=watch->Chart1->GetFreeSeriesColor(true);
 else
  wd.Color=color;

 wd.Y=&(itemd->GetOutputData(output).Double[outindex]);
 wd.XYSize=1;
 wd.Style=style;
 watch->Add(wd);
}

// Добавляем посторонний объект в окно наблюдений (график по времени)
void AddWatch(TUWatchFrame *watch, NameT name, double *y, double watchinterval, double yshift, TPenStyle style, TColor color)
{
 if(!watch || !y)
  return;

 TUWatchInfo wd;
 wd.FullUpdate=false;
 wd.WatchInterval=watchinterval;
// wd.X=&UContainer::GetDoubleTime();

 wd.YShift=yshift;
 wd.Legend=name;
// wd.DataSource=0;

 if(color == 0) // Подбор подходящего цвета
  wd.Color=watch->Chart1->GetFreeSeriesColor(true);
 else
  wd.Color=color;

 wd.Y=y;
 wd.XYSize=1;
 wd.Style=style;
 watch->Add(wd);
}


// Добавляем объект в окно наблюдений (график по частоте)
void AddFrequencyWatch(TUWatchFrame *watch, RDK::UContainer* item, double watchinterval, double yshift, TPenStyle style, TColor color)
{
 NFrequencyReceiver *itemd=dynamic_cast<NFrequencyReceiver*>(item);

 if(!itemd || !watch)
  return;

 TUWatchInfo wd;
 wd.FullUpdate=true;
 wd.WatchInterval=watchinterval;
 wd.X=&itemd->GetXResult()[0];

 wd.YShift=yshift;
 if(itemd->GetOwner())
  itemd->GetLongName(static_pointer_cast<RDK::UContainer>(itemd->GetOwner()->GetOwner()),wd.Legend);
 else
  itemd->GetLongName(0,wd.Legend);
// wd.Legend+=string("[")+sntoa(output)+string(":")+sntoa(outindex)+string("]");
// wd.DataSource=item;

 if(color == 0) // Подбор подходящего цвета
  wd.Color=watch->Chart1->GetFreeSeriesColor(true);
 else
  wd.Color=color;

 wd.Y=&itemd->GetYResult()[0];
 wd.XYSize=itemd->GetYResult().size();
 wd.Style=style;
 watch->Add(wd);
}



}
#endif
