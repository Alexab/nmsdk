#-------------------------------------------------
#
# Project created by QtCreator 2016-07-25T14:35:21
#
#-------------------------------------------------

QT       += core
QT       -= gui

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets #printsupport

TARGET = NeuroModelerConsole
TEMPLATE = app

include($$PWD/../../../Rdk/Build/Lib/Qt/RdkDefines.pri)

windows {
message("Using "msvc-$$(VisualStudioVersion) compiler)
DESTDIR = $$PWD/../../../Bin/Platform/Win/
    LIBS += -L$$(ANACONDA_PATH)/libs/

} else {
DESTDIR = $$PWD/../../../Bin/Platform/Linux/
}

windows:msvc {
 QMAKE_CXXFLAGS += /bigobj
}

CONFIG -= debug_and_release debug_and_release_target
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += console

DEFINES += QT_DLL QT_WIDGETS_LIB

VERSION = $$system(hg parents --template '{rev}')
DEFINES += RDK_APP_VERSION=$$VERSION

INCLUDEPATH += ../../../Gui/Qt \
    ../../../Deploy/Include \
    ../../../Rdk/Core/Graphics \
    GeneratedFiles \
    GeneratedFiles/Debug \
    ../../../Rdk/Deploy/Include \
    ../../../Rdk/GUI/Qt

unix {
INCLUDEPATH += /usr/local/include
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
 OPENCV_LIBS_VERSION = 345
 OPENCV_COMPILED_VERSION_64 = vc15
 OPENCV_COMPILED_VERSION_86 = vc15

 # функция добавляет постфикс(второй параметр) ко всем элементам первого входного параметра
 defineReplace(addPostfix) {
  libList = $$1
  for(lib, libList) {
   returnValue += $${lib}$${2}
  }
  return($$returnValue)
 }

 INCLUDEPATH += $$(OPENCV3_PATH)/build/include

 !contains(QMAKE_TARGET.arch, x86_64) {
 CONFIG(debug){
  LIBS += -L$$(OPENCV3_PATH)/build/x86/$${OPENCV_COMPILED_VERSION_86}/lib/Debug $$addPostfix($$OPENCV_LIBS_LIST, $${OPENCV_LIBS_VERSION}d)
 }
 CONFIG(release) {
  LIBS += -L$$(OPENCV3_PATH)/build/x86/$${OPENCV_COMPILED_VERSION_86}/lib/Release $$addPostfix($$OPENCV_LIBS_LIST, $${OPENCV_LIBS_VERSION})
 }
} else {
 CONFIG(debug){
  LIBS += -L$$(OPENCV3_PATH)/build/x64/$${OPENCV_COMPILED_VERSION_64}/lib/Debug $$addPostfix($$OPENCV_LIBS_LIST, $${OPENCV_LIBS_VERSION}d)
 }
 CONFIG(release) {
  LIBS += -L$$(OPENCV3_PATH)/build/x64/$${OPENCV_COMPILED_VERSION_64}/lib/Release $$addPostfix($$OPENCV_LIBS_LIST, $${OPENCV_LIBS_VERSION})
 }
}
} else:unix {
 LIBS += $$OPENCV_LIBS_LIST
}

#including boost

windows {
 BOOST_COMPILED_VERSION = msvc-$$(VisualStudioVersion)

 INCLUDEPATH += $$(BOOST_PATH)
!contains(QMAKE_TARGET.arch, x86_64) {
 LIBS += -L$$(BOOST_PATH)/$${BOOST_COMPILED_VERSION}-x86/lib/
} else {
 LIBS += -L$$(BOOST_PATH)/$${BOOST_COMPILED_VERSION}-x64/lib/
}
} else:unix {
 LIBS += -lboost_thread \
  -lboost_system \
  -lboost_program_options \
  -lboost_python$${RDK_PYTHON_MAJOR}$${RDK_PYTHON_MINOR} \
  -lboost_numpy$${RDK_PYTHON_MAJOR}$${RDK_PYTHON_MINOR} \
  -lpython3.5m \
  -lpthread
}

SOURCES += \
        ../../../Libraries/Libraries.cpp \
        main.cpp \ #\
    ../../../Rdk/GUI/Qt/UEngineControlQt.cpp
#    ../../../Rdk/GUI/Qt/UComponentsListWidget.cpp \
#    ../../../Rdk/GUI/Qt/UGEngineControllWidget.cpp \
#    ../../../Rdk/GUI/Qt/UVisualControllerWidget.cpp \
#    ../../../Rdk/GUI/Qt/UDrawEngineWidget.cpp \
#    ../../../Rdk/GUI/Qt/UDrawEngineImageWidget.cpp \
#    ../../../Rdk/GUI/Qt/UClassesListWidget.cpp \
#    ../../../Rdk/GUI/Qt/UComponentLinksWidget.cpp \
#    ../../../Rdk/GUI/Qt/UImagesWidget.cpp \
#    ../../../Rdk/GUI/Qt/USingleImageWidget.cpp \
#    ../../../Rdk/GUI/Qt/UComponentPropertySelectionWidget.cpp \
#    ../../../Rdk/GUI/Qt/UPropertyXMLWidget.cpp \
#    ../../../Rdk/GUI/Qt/UCalculationChannelsWidget.cpp \
#    ../../../Rdk/GUI/Qt/UEngineControlQt.cpp \
#    ../../../Rdk/GUI/Qt/ULoggerWidget.cpp \
#    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.cpp \
#    ../../../Rdk/GUI/Qt/UImageLoader.cpp \
#    ../../../Rdk/GUI/Qt/UCreateTestWidget.cpp \
#    ../../../Rdk/GUI/Qt/UComponentPropertyChanger.cpp \
#    ../../../Rdk/GUI/Qt/UStatusPanel.cpp \
#    ../../../Rdk/GUI/Qt/USingleImagePainter.cpp \
#    ../../../Rdk/GUI/Qt/qcustomplot.cpp \
#    ../../../Rdk/GUI/Qt/UGraphWidget.cpp \
#    ../../../Rdk/GUI/Qt/UGraphControlDialog.cpp \
#    ../../../Rdk/GUI/Qt/UGraphPaintWidget.cpp \
#    ../../../Rdk/GUI/Qt/UTableInfo.cpp

HEADERS += \
        ../../../Libraries/Libraries.h \
#    ../../../Rdk/GUI/Qt/UComponentsListWidget.h \
#    ../../../Rdk/GUI/Qt/UGEngineControllWidget.h \
#    ../../../Rdk/GUI/Qt/UVisualControllerWidget.h \
#    ../../../Rdk/GUI/Qt/UDrawEngineWidget.h \
#    ../../../Rdk/GUI/Qt/UDrawEngineImageWidget.h \
#    ../../../Rdk/GUI/Qt/UClassesListWidget.h \
#    ../../../Rdk/GUI/Qt/UComponentLinksWidget.h \
#    ../../../Rdk/GUI/Qt/UImagesWidget.h \
#    ../../../Rdk/GUI/Qt/USingleImageWidget.h \
#    ../../../Rdk/GUI/Qt/UComponentPropertySelectionWidget.h \
#    ../../../Rdk/GUI/Qt/UPropertyXMLWidget.h \
#    ../../../Rdk/GUI/Qt/UCalculationChannelsWidget.h \
#    ../../../Rdk/GUI/Qt/UEngineControlQt.h \
#    ../../../Rdk/GUI/Qt/ULoggerWidget.h \
#    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.h \
#    ../../../Rdk/GUI/Qt/USingleImagePainter.h \
#    ../../../Rdk/GUI/Qt/UImageLoader.h \
#    ../../../Rdk/GUI/Qt/UCreateTestWidget.h \
#    ../../../Rdk/GUI/Qt/UComponentPropertyChanger.h \
#    ../../../Rdk/GUI/Qt/UStatusPanel.h \
#    ../../../Rdk/GUI/Qt/USettingsReaderWidget.h \
#    ../../../Rdk/GUI/Qt/qcustomplot.h \
#    ../../../Rdk/GUI/Qt/UGraphWidget.h \
#    ../../../Rdk/GUI/Qt/UStructSingleGraph.h \
#    ../../../Rdk/GUI/Qt/UGraphControlDialog.h \
#    ../../../Rdk/GUI/Qt/UGraphPaintWidget.h \
#    ../../../Rdk/GUI/Qt/UTableInfo.h
    ../../../Rdk/GUI/Qt/UEngineControlQt.h

#FORMS   += \
#    ../../../Rdk/GUI/Qt/UComponentsListWidget.ui \
#    ../../../Rdk/GUI/Qt/UGEngineControllWidget.ui \
#    ../../../Rdk/GUI/Qt/UDrawEngineWidget.ui \
#    ../../../Rdk/GUI/Qt/UClassesListWidget.ui \
#    ../../../Rdk/GUI/Qt/UComponentLinksWidget.ui \
#    ../../../Rdk/GUI/Qt/UImagesWidget.ui \
#    ../../../Rdk/GUI/Qt/USingleImageWidget.ui \
#    ../../../Rdk/GUI/Qt/UComponentPropertySelectionWidget.ui \
#    ../../../Rdk/GUI/Qt/UPropertyXMLWidget.ui \
#    ../../../Rdk/GUI/Qt/UCalculationChannelsWidget.ui \
#    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.ui \
#    ../../../Rdk/GUI/Qt/UCreateTestWidget.ui \
#    ../../../Rdk/GUI/Qt/UComponentPropertyChanger.ui \
#    ../../../Rdk/GUI/Qt/UStatusPanel.ui \
#    ../../../Rdk/GUI/Qt/UGraphWidget.ui \
#    ../../../Rdk/GUI/Qt/UGraphControlDialog.ui \
#    ../../../Rdk/GUI/Qt/UGraphPaintWidget.ui \
#    ../../../Rdk/GUI/Qt/UTableInfo.ui
