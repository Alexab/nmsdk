//---------------------------------------------------------------------------

#pragma hdrstop

#include <tchar.h>
#include "NEngine.h"

NMSDK::NEngine Engine;
//---------------------------------------------------------------------------

#pragma argsused
int _tmain(int argc, _TCHAR* argv[])
{
 Engine.Default();
 Engine.Init();

 NMSDK::NAContainer *net=0;
 string mename;
 mename=string("NBranchedCrosslinksEngineControlRangeAfferent")+MySDK::sntoa(5);

 net=static_cast<NMSDK::NAContainer*>(Engine.GetEnvironment()->GetStorage()->TakeObject(mename));
 if(net)
 {
  net->Name="EngineControl";
 }

 Engine.Run();

 Engine.UnInit();
	return 0;
}
//---------------------------------------------------------------------------
