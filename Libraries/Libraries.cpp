//#ifndef RTV_DEBUG_LIBRARIES_CPP
//#define RTV_DEBUG_LIBRARIES_CPP

#include "Libraries.h"

#ifdef __BORLANDC__

#pragma link "../../../Rdk/Bin/Platform/Win/libcurl.bcb.lib"
#pragma link "../../../Rdk/Bin/Platform/Win/rdk.bcb.static.lib"
#pragma link "../../../Libraries/Rdk-BasicLib/Bin/Bcb/Rdk-BasicLib.lib"
#pragma link "../../../Libraries/Rdk-BasicStatisticLib/Bin/Bcb/Rdk-BasicStatisticLib.lib"
#pragma link "../../../Libraries/Rdk-IoLib/Bin/Bcb/Rdk-IoLib.lib"
#pragma link "../../../Libraries/Rdk-SourcesLib/Bin/Bcb/Rdk-SourcesLib.lib"

#pragma link "../../../Libraries/Nmsdk-ActLib/Bin/Bcb/Nmsdk-ActLib.lib"
#pragma link "../../../Libraries/Nmsdk-BasicLib/Bin/Bcb/Nmsdk-BasicLib.lib"
#pragma link "../../../Libraries/Nmsdk-MathLib/Bin/Bcb/Nmsdk-MathLib.lib"
#pragma link "../../../Libraries/Nmsdk-MotionControlLib/Bin/Bcb/Nmsdk-MotionControlLib.lib"
#pragma link "../../../Libraries/Nmsdk-NeuronLifeLib/Bin/Bcb/Nmsdk-NeuronLifeLib.lib"
#pragma link "../../../Libraries/Nmsdk-PhysLib/Bin/Bcb/Nmsdk-PhysLib.lib"
#pragma link "../../../Libraries/Nmsdk-PulseLib/Bin/Bcb/Nmsdk-PulseLib.lib"
#pragma link "../../../Libraries/Nmsdk-PulseNeuronLib/Bin/Bcb/Nmsdk-PulseNeuronLib.lib"
#pragma link "../../../Libraries/Nmsdk-ReceiverLib/Bin/Bcb/Nmsdk-ReceiverLib.lib"
#pragma link "../../../Libraries/Nmsdk-SensorLib/Bin/Bcb/Nmsdk-SensorLib.lib"
#pragma link "../../../Libraries/Nmsdk-SourceLib/Bin/Bcb/Nmsdk-SourceLib.lib"
#endif

#ifdef _MSC_VER
#pragma comment( lib, "../../../../Rdk/Bin/Platform/Win/libcurl.bcb.lib")
#pragma comment( lib, "../../../../Rdk/Bin/Platform/Win/rdk.bcb.static.lib")
#pragma comment( lib, "../../../../Libraries/Rdk-BasicLib/Bin/Vs/Rdk-BasicLib.lib")
#pragma comment( lib, "../../../../Libraries/Rdk-BasicStatisticLib/Bin/Vs/Rdk-BasicStatisticLib.lib")
#pragma comment( lib, "../../../../Libraries/Rdk-IoLib/Bin/Vs/Rdk-IoLib.lib")
#pragma comment( lib, "../../../../Libraries/Rdk-SourcesLib/Bin/Vs/Rdk-SourcesLib.lib")

#pragma comment( lib, "../../../../Libraries/Nmsdk-ActLib/Bin/Bcb/Nmsdk-ActLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-BasicLib/Bin/Bcb/Nmsdk-BasicLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-MathLib/Bin/Bcb/Nmsdk-MathLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-MotionControlLib/Bin/Bcb/Nmsdk-MotionControlLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-NeuronLifeLib/Bin/Bcb/Nmsdk-NeuronLifeLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-PhysLib/Bin/Bcb/Nmsdk-PhysLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-PulseLib/Bin/Bcb/Nmsdk-PulseLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-PulseNeuronLib/Bin/Bcb/Nmsdk-PulseNeuronLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-ReceiverLib/Bin/Bcb/Nmsdk-ReceiverLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-SensorLib/Bin/Bcb/Nmsdk-SensorLib.lib")
#pragma comment( lib, "../../../../Libraries/Nmsdk-SourceLib/Bin/Bcb/Nmsdk-SourceLib.lib")
#endif

namespace RDK {

/// Функция должна быть реализована в конечном проекте и загружать требуемые библиотеки
bool RDK_CALL RdkLoadPredefinedLibraries(std::list<RDK::ULibrary*> &libs_list)
{
 using namespace NMSDK;
 RDK::UItemData::DefaultDataSize=sizeof(double);
 libs_list.push_back(&RDK::BCLLibrary);
 libs_list.push_back(&RDK::IOLibrary);
// libs_list.push_back(&CRLibrary);
 libs_list.push_back(&RDK::StatisticLibrary);
 libs_list.push_back(&RDK::SourceLibrary);

 libs_list.push_back(&NMSDK::BCLLibrary);
 libs_list.push_back(&NMSDK::ActLibrary);
 libs_list.push_back(&NMSDK::MathLibrary);
 libs_list.push_back(&NMSDK::PhysLibrary);
 libs_list.push_back(&NMSDK::SensorLibrary);
 libs_list.push_back(&NMSDK::NeuronSourceLibrary);
 libs_list.push_back(&NMSDK::ReceiverLibrary);
 libs_list.push_back(&NMSDK::PulseLibrary);
 libs_list.push_back(&NMSDK::NeuronLifeLibrary);
 libs_list.push_back(&NMSDK::PulseNeuronLibrary);
 libs_list.push_back(&NMSDK::MotionControlLibrary);
 libs_list.push_back(&NMSDK::WinAPIActLibrary);

 return true;
}

/// Функция должна быть реализована в конечном проекте
bool RDK_CALL RdkCreatePredefinedStructure(RDK::UEnvironment* env, int predefined_structure)
{
 return true;
}

}


//#endif
