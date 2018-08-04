// NConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NEngine.h"

NMSDK::NEngine Engine;


int _tmain(int argc, _TCHAR* argv[])
{
 Engine.Default();
 Engine.Init();

 NMSDK::NAContainer *net=0;
 string mename;
 mename=string("NBranchedCrosslinksEngineControlRangeAfferent")+MySDK::sntoa(5);

 net=Engine.GetEnvironment()->GetStorage()->TakeObject(mename);
 if(net)
 {
  net->Name="EngineControl";
 }

 Engine.Run();

 Engine.UnInit();
 return 0;
}

