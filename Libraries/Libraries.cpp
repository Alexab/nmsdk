//#ifndef RTV_DEBUG_LIBRARIES_CPP
//#define RTV_DEBUG_LIBRARIES_CPP

#include "Libraries.h"

namespace RDK {

/// Функция должна быть реализована в конечном проекте и загружать требуемые библиотеки
bool RDK_CALL RdkLoadPredefinedLibraries(std::list<RDK::ULibrary*> &libs_list)
{
 using namespace NMSDK;
// RDK::UItemData::DefaultDataSize=sizeof(double);
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
 libs_list.push_back(&NMSDK::PulseClassicModelsLib);

 return true;
}

/// Функция должна быть реализована в конечном проекте
bool RDK_CALL RdkCreatePredefinedStructure(RDK::UEnvironment* env, int predefined_structure)
{
 return true;
}

}


//#endif
