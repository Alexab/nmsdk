TEMPLATE = subdirs

defineReplace(addSubdirsRdkNmsdk) {
    for(name, 1) {
        SUBDIRS += $$name
        eval($${name}.file = $$PWD/../../../Libraries/$${name}/Build/Qt/$${name}.pro)
        export($${name}.file)
    }
    export(SUBDIRS)
    return(1)
}

Rdk_Nmsdk_libs = Rdk-BasicLib \
        Rdk-BasicStatisticLib \
        Rdk-IoLib \
        Rdk-SourcesLib \
        Rdk-CRLib \
        Rdk-CvAriphmeticLib \
        Rdk-CvBasicLib \
        Rdk-CvDetectionLib \
        Rdk-CvGuiLib \
        Rdk-CvSimulatorLib \
        Rdk-CvStatisticLib \
        Rdk-CvVideoCaptureLib \
        Rdk-PyMachineLearningLib \
        Rdk-NoiseGenLib \
        Nmsdk-ActLib \
        Nmsdk-BasicLib \
        Nmsdk-MathLib \
        Nmsdk-MotionControlLib \
        Nmsdk-NeuronLifeLib \
        Nmsdk-PhysLib \
        Nmsdk-PulseClassicModelsLib \
        Nmsdk-PulseLib \
        Nmsdk-PulseNeuronLib \
        Nmsdk-ReceiverLib \
        Nmsdk-SensorLib \
        Nmsdk-SourceLib

$$addSubdirsRdkNmsdk($$Rdk_Nmsdk_libs)


windows {
    SUBDIRS += curl
    curl.file = $$PWD/../../../Rdk/ThirdParty/curl/build/qt/curl.pro
}

SUBDIRS +=  rdk-static-qt

rdk-static-qt.file = $$PWD/../../../Rdk/Build/Lib/Qt/rdk.static.qt.pro
