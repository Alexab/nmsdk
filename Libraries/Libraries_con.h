#ifndef NMSDK_LIBRARIES_H
#define NMSDK_LIBRARIES_H

#include "../Rdk/Deploy/Include/rdk.h"

#include "Rdk-BasicLib/Deploy/Include/Lib.h"
#include "Rdk-BasicStatisticLib/Deploy/Include/Lib.h"
#include "Rdk-IoLib/Deploy/Include/Lib.h"
#include "Rdk-SourcesLib/Deploy/Include/Lib.h"
#include "Rdk-CvVideoCaptureLib/Core/VideoCap.h"
#include "Rdk-CvAriphmeticLib/Deploy/Include/Lib.h"
#include "Rdk-CvBasicLib/Deploy/Include/Lib.h"
#include "Rdk-CvDetectionLib/Deploy/Include/Lib.h"
#include "Rdk-CvGuiLib/Deploy/Include/Lib.h"
#include "Rdk-CvStatisticLib/Deploy/Include/Lib.h"
#include "Rdk-CvSimulatorLib/Deploy/Include/Lib.h"
#include "Rdk-CRLib/Deploy/Include/Lib.h"
#include "Rdk-NoiseGenLib/Deploy/Include/Lib.h"
#include "Rdk-CvVideoCaptureLib/Core/VideoCap.h"
//#include "Rdk-TensorflowLib/Core/UTensorflowLib.h"
#include "Nmsdk-ActLib/Deploy/Include/Lib.h"
#include "Nmsdk-BasicLib/Deploy/Include/Lib.h"
#include "Nmsdk-MathLib/Deploy/Include/Lib.h"
//#include "Nmsdk-MotionControlLib/Deploy/Include/Lib.h"
#include "Nmsdk-NeuronLifeLib/Deploy/Include/Lib.h"
#include "Nmsdk-PhysLib/Deploy/Include/Lib.h"
#include "Nmsdk-PulseLib/Deploy/Include/Lib.h"
//#include "Nmsdk-PulseNeuronLib/Deploy/Include/Lib.h"
#include "Nmsdk-ReceiverLib/Deploy/Include/Lib.h"
#include "Nmsdk-SensorLib/Deploy/Include/Lib.h"
#include "Nmsdk-SourceLib/Deploy/Include/Lib.h"
#include "Nmsdk-PulseClassicModelsLib/Core/Lib.h"
#include "Rdk-PyMachineLearningLib/Core/Lib.h"

namespace RDK {

/// Функция должна быть реализована в конечном проекте и загружать требуемые библиотеки
extern RDK_LIB_TYPE bool RDK_CALL RdkLoadPredefinedLibraries(std::list<RDK::ULibrary*> &libs_list);

/// Функция должна быть реализована в конечном проекте
extern RDK_LIB_TYPE bool RDK_CALL RdkCreatePredefinedStructure(RDK::UEnvironment* env, int predefined_structure);

}

#endif
