#-------------------------------------------------
#
# Project created by QtCreator 2016-07-25T14:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = NeuroModeler
TEMPLATE = app

windows {
DESTDIR = $$PWD/../../../Bin/Platform/Win/
}
else {
DESTDIR = $$PWD/../../../Bin/Platform/Linux/
}

windows:msvc {
 QMAKE_CXXFLAGS += /bigobj
}

CONFIG -= debug_and_release debug_and_release_target

DEFINES += QT_DLL QT_WIDGETS_LIB
DEFINES += LIBRDK_LIBRARY_EXPORT
DEFINES += RDK_UNICODE_RUN
DEFINES += RDK_QT

INCLUDEPATH += ../../../Gui/Qt \
    ../../../Deploy/Include \
    ../../../Rdk/Core/Graphics \
    GeneratedFiles \
    GeneratedFiles/Debug \
    ../../../Rdk/Deploy/Include \
    ../../../Rdk/GUI/Qt

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

#including boost

windows {
 INCLUDEPATH += $$(BOOST_PATH)
 LIBS += -L$$(BOOST_PATH)/lib32-msvc-10.0/
} else:unix {
 LIBS += -lboost_thread \
  -lboost_system \
  -lboost_program_options \
  -lpthread
}

#windows-msvc*{
# INCLUDEPATH += $$(BOOST_PATH)/include/boost-1_54

# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_chrono-vc100-mt-gd-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_date_time-vc100-mt-gd-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_regex-vc100-mt-gd-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_system-vc100-mt-gd-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_thread-vc100-mt-gd-1_54.lib

# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_chrono-vc100-mt-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_date_time-vc100-mt-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_regex-vc100-mt-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_system-vc100-mt-1_54.lib
# LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_thread-vc100-mt-1_54.lib

# #LIBS += $$(BOOST_PATH)/lib/libboost_atomic-vc100-mt-gd-1_54.lib
# #LIBS += $$(BOOST_PATH)/lib/libboost_signals-vc100-mt-gd-1_54.lib
# #LIBS += $$(BOOST_PATH)/lib/libboost_timer-vc100-mt-gd-1_54.lib

# #LIBS += $$(BOOST_PATH)/lib/libboost_atomic-vc100-mt-1_54.lib
# #LIBS += $$(BOOST_PATH)/lib/libboost_signals-vc100-mt-1_54.lib
# #LIBS += $$(BOOST_PATH)/lib/libboost_timer-vc100-mt-1_54.lib
#}

#win32-g++{
# INCLUDEPATH += $$(BOOST_PATH)/include/boost-1_54

# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_chrono-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_date_time-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_regex-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_system-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_thread-mgw49-mt-1_54

# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_chrono-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_date_time-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_regex-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_system-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_thread-mgw49-mt-1_54
# LIBS += $$(BOOST_PATH)/lib32-mgw492/lib/libboost_program_options-mgw49-mt-1_54

#} else:unix {
# LIBS += -lboost_thread
# LIBS += -lboost_system
# LIBS += -lpthread
# LIBS += -lboost_program_options
# LIBS += -lboost_chrono
# LIBS += -lboost_system
#}


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
    ../../../Rdk/GUI/Qt/USingleImagePainter.cpp \
    ../../../Rdk/GUI/Qt/qcustomplot.cpp \
    ../../../Rdk/GUI/Qt/UGraphWidget.cpp \
    ../../../Rdk/GUI/Qt/UGraphControlDialog.cpp \
    ../../../Rdk/GUI/Qt/UGraphPaintWidget.cpp

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
    ../../../Rdk/GUI/Qt/USettingsReaderWidget.h \
    ../../../Rdk/GUI/Qt/qcustomplot.h \
    ../../../Rdk/GUI/Qt/UGraphWidget.h \
    ../../../Rdk/GUI/Qt/UStructSingleGraph.h \
    ../../../Rdk/GUI/Qt/UGraphControlDialog.h \
    ../../../Rdk/GUI/Qt/UGraphPaintWidget.h

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
    ../../../Rdk/GUI/Qt/UStatusPanel.ui \
    ../../../Rdk/GUI/Qt/UGraphWidget.ui \
    ../../../Rdk/GUI/Qt/UGraphControlDialog.ui \
    ../../../Rdk/GUI/Qt/UGraphPaintWidget.ui
