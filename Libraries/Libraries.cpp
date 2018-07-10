#include "Libraries.h"

namespace RDK {

/// Функция должна быть реализована в конечном проекте и загружать требуемые библиотеки
bool RDK_CALL RdkLoadPredefinedLibraries(std::list<RDK::ULibrary*> &libs_list)
{
 using namespace NMSDK;
// RDK::UItemData::DefaultDataSize=sizeof(double);
 libs_list.push_back(&RDK::BCLLibrary);
 libs_list.push_back(&RDK::IOLibrary);
 libs_list.push_back(&RDK::CRLibrary);
 libs_list.push_back(&RDK::StatisticLibrary);
 libs_list.push_back(&RDK::SourceLibrary);
 libs_list.push_back(&RDK::RDKVideoCaptureLibrary);
 libs_list.push_back(&RDK::AriphmeticLibrary);
 libs_list.push_back(&RDK::BasicLibrary);
 libs_list.push_back(&RDK::DetectionLibrary);
 libs_list.push_back(&RDK::GUILibrary);
 libs_list.push_back(&RDK::SimulatorLibrary);
 libs_list.push_back(&RDK::BStatisticLibrary);
 libs_list.push_back(&RDK::NoiseLibrary);
#ifndef __BORLANDC__
 libs_list.push_back(&RDK::PyMachineLearningLib);
#endif


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
 #ifndef NMSDK_DEBUG
 libs_list.push_back(&NMSDK::MotionControlLibrary);
 #endif
 #ifndef __GNUC__
 libs_list.push_back(&NMSDK::WinAPIActLibrary);
 #endif
 libs_list.push_back(&NMSDK::PulseClassicModelsLib);


 return true;
}

/// Функция должна быть реализована в конечном проекте
bool RDK_CALL RdkCreatePredefinedStructure(RDK::UEnvironment* env, int predefined_structure)
{
 return true;
}

}
