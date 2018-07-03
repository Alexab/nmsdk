#-------------------------------------------------
#
# Project created by QtCreator 2016-07-25T14:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NeuroModeler
TEMPLATE = app

windows {
DESTDIR = $$PWD/../../../Bin/Platform/Win/
    INCLUDEPATH += d:/Anaconda3/include/
    INCLUDEPATH += $$(BOOST_PATH)
    INCLUDEPATH += $$(OPENCV3_PATH)/build/include
    INCLUDEPATH += d:/Anaconda3/Lib/site-packages/numpy/core/include/numpy

    LIBS += -Ld:/Anaconda3/libs/

} else {
DESTDIR = $$PWD/../../../Bin/Platform/Linux/
    INCLUDEPATH += /usr/include/python3.5
}

windows:msvc {
 QMAKE_CXXFLAGS += /bigobj
}

CONFIG -= debug_and_release debug_and_release_target

DEFINES += QT_DLL QT_WIDGETS_LIB
DEFINES += LIBRDK_LIBRARY_EXPORT
DEFINES += RDK_UNICODE_RUN
DEFINES += RDK_QT
#DEFINES += BOOST_LIB_NAME boost_python35

INCLUDEPATH += ../../../Gui/Qt \
    ../../../Deploy/Include \
    ../../../Rdk/Core/Graphics \
    GeneratedFiles \
    GeneratedFiles/Debug \
    ../../../Rdk/Deploy/Include \
    ../../../Rdk/GUI/Qt

unix {
INCLUDEPATH += /usr/include/python3.5
#INCLUDEPATH += /usr/local/include/boost
#INCLUDEPATH += /usr/local/lib64
#INCLUDEPATH += /usr/include/numpy
#INCLUDEPATH += /usr/local/include/opencv
}

MOC_DIR = GeneratedFiles/release

OBJECTS_DIR = release

UI_DIR = GeneratedFiles

RCC_DIR = GeneratedFiles

#including our libs
NMSDK_LIBS_NAMES = \
 Rdk-BasicStatisticLib \
 Rdk-BasicLib \
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
 Nmsdk-SourceLib \
 rdk.static



windows:!windows-g++ {

 for(lib, NMSDK_LIBS_NAMES) {
  NMSDK_LIBS_LIST += -l$${lib}.qt
  NMSDK_LIBS_FILES += $$PWD/../../../Bin/Platform/Win/Lib.Qt/$${lib}.qt.lib
 }

 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ $$NMSDK_LIBS_LIST -lcurl.qt
 PRE_TARGETDEPS += $$NMSDK_LIBS_FILES

} else:unix {

 for(lib, NMSDK_LIBS_NAMES) {
  NMSDK_LIBS_LIST += -l$${lib}.qt
  NMSDK_LIBS_FILES += $$PWD/../../../Bin/Platform/Linux/Lib.Qt/lib$${lib}.qt.a
 }
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ $$NMSDK_LIBS_LIST
 PRE_TARGETDEPS += $$NMSDK_LIBS_FILES
}

#including opencv
OPENCV_LIBS_LIST = -L/usr/local/lib/ -lopencv_core \
 -L/usr/local/lib/ -lopencv_highgui \
 -L/usr/local/lib/ -lopencv_imgproc \
 -L/usr/local/lib/ -lopencv_videoio \
 -L/usr/local/lib/ -lopencv_video \
 -L/usr/local/lib/ -lopencv_imgcodecs

windows {
 OPENCV_LIBS_VERSION = 310

 # функция добавляет постфикс(второй параметр) ко всем элементам первого входного параметра
 defineReplace(addPostfix) {
  libList = $$1
  for(lib, libList) {
   returnValue += $${lib}$${2}
  }
  return($$returnValue)
 }

 INCLUDEPATH += $$(OPENCV3_PATH)/build/include

 CONFIG(debug){
  LIBS += -L$$(OPENCV3_PATH)/build/x64/Vc12/lib/Debug $$addPostfix($$OPENCV_LIBS_LIST, $${OPENCV_LIBS_VERSION}d)
 }
 CONFIG(release){
  LIBS += -L$$(OPENCV3_PATH)/build/x64/Vc12/lib/Release $$addPostfix($$OPENCV_LIBS_LIST, $${OPENCV_LIBS_VERSION})
 }

} else:unix {
 LIBS += $$OPENCV_LIBS_LIST
}

#including boost

windows {
 INCLUDEPATH += $$(BOOST_PATH)
 LIBS += -L$$(BOOST_PATH)/msvc-12.0-x64/lib/
 LIBS += -L$$(BOOST_PATH)/msvc-12.0-x64/lib/ -llibboost_numpy35-vc120-mt-x64-1_67
} else:unix {
 LIBS += -lboost_thread \
  -lboost_system \
  -lboost_program_options \
  -lboost_python3 \
  -lpython3.5m \
  -lboost_numpy \
  -lpthread

# LIBS += /usr/lib/x86_64-linux-gnu/libboost_python-py35.so
# LIBS += /usr/lib/x86_64-linux-gnu/libpython3.5m.so
# LIBS += /usr/local/lib64/libboost_numpy.so
}

SOURCES += \
        ../../../Libraries/Libraries.cpp \
        main.cpp\
    ../../../Rdk/GUI/Qt/UComponentsListWidget.cpp \
    ../../../Rdk/GUI/Qt/UGEngineControllWidget.cpp \
    ../../../Rdk/GUI/Qt/UVisualControllerWidget.cpp \
    ../../../Rdk/GUI/Qt/UDrawEngineWidget.cpp \
    ../../../Rdk/GUI/Qt/UDrawEngineImageWidget.cpp \
    ../../../Rdk/GUI/Qt/UClassesListWidget.cpp \
    ../../../Rdk/GUI/Qt/UComponentLinksWidget.cpp \
    ../../../Rdk/GUI/Qt/UImagesWidget.cpp \
    ../../../Rdk/GUI/Qt/USingleImageWidget.cpp \
    ../../../Rdk/GUI/Qt/UComponentPropertySelectionWidget.cpp \
    ../../../Rdk/GUI/Qt/UPropertyXMLWidget.cpp \
    ../../../Rdk/GUI/Qt/UCalculationChannelsWidget.cpp \
    ../../../Rdk/GUI/Qt/UEngineControlQt.cpp \
    ../../../Rdk/GUI/Qt/ULoggerWidget.cpp \
    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.cpp \
    ../../../Rdk/GUI/Qt/UImageLoader.cpp \
    ../../../Rdk/GUI/Qt/UCreateTestWidget.cpp \
    ../../../Rdk/GUI/Qt/UComponentPropertyChanger.cpp \
    ../../../Rdk/GUI/Qt/UStatusPanel.cpp \
    ../../../Rdk/GUI/Qt/USingleImagePainter.cpp

HEADERS += \
        ../../../Libraries/Libraries.h \
    ../../../Rdk/GUI/Qt/UComponentsListWidget.h \
    ../../../Rdk/GUI/Qt/UGEngineControllWidget.h \
    ../../../Rdk/GUI/Qt/UVisualControllerWidget.h \
    ../../../Rdk/GUI/Qt/UDrawEngineWidget.h \
    ../../../Rdk/GUI/Qt/UDrawEngineImageWidget.h \
    ../../../Rdk/GUI/Qt/UClassesListWidget.h \
    ../../../Rdk/GUI/Qt/UComponentLinksWidget.h \
    ../../../Rdk/GUI/Qt/UImagesWidget.h \
    ../../../Rdk/GUI/Qt/USingleImageWidget.h \
    ../../../Rdk/GUI/Qt/UComponentPropertySelectionWidget.h \
    ../../../Rdk/GUI/Qt/UPropertyXMLWidget.h \
    ../../../Rdk/GUI/Qt/UCalculationChannelsWidget.h \
    ../../../Rdk/GUI/Qt/UEngineControlQt.h \
    ../../../Rdk/GUI/Qt/ULoggerWidget.h \
    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.h \
    ../../../Rdk/GUI/Qt/USingleImagePainter.h \
    ../../../Rdk/GUI/Qt/UImageLoader.h \
    ../../../Rdk/GUI/Qt/UCreateTestWidget.h \
    ../../../Rdk/GUI/Qt/UComponentPropertyChanger.h \
    ../../../Rdk/GUI/Qt/UStatusPanel.h \
    ../../../Rdk/GUI/Qt/USettingsReaderWidget.h

FORMS   += \
    ../../../Rdk/GUI/Qt/UComponentsListWidget.ui \
    ../../../Rdk/GUI/Qt/UGEngineControllWidget.ui \
    ../../../Rdk/GUI/Qt/UDrawEngineWidget.ui \
    ../../../Rdk/GUI/Qt/UClassesListWidget.ui \
    ../../../Rdk/GUI/Qt/UComponentLinksWidget.ui \
    ../../../Rdk/GUI/Qt/UImagesWidget.ui \
    ../../../Rdk/GUI/Qt/USingleImageWidget.ui \
    ../../../Rdk/GUI/Qt/UComponentPropertySelectionWidget.ui \
    ../../../Rdk/GUI/Qt/UPropertyXMLWidget.ui \
    ../../../Rdk/GUI/Qt/UCalculationChannelsWidget.ui \
    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.ui \
    ../../../Rdk/GUI/Qt/UCreateTestWidget.ui \
    ../../../Rdk/GUI/Qt/UComponentPropertyChanger.ui \
    ../../../Rdk/GUI/Qt/UStatusPanel.ui
