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
 QMAKE_CXXFLAGS += /bigobj
}
else {
DESTDIR = $$PWD/../../../Bin/Platform/Linux/
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
windows:!windows-g++ {
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lrdk.static.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lRdk-BasicLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lRdk-BasicStatisticLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lRdk-IoLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lRdk-SourcesLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-ActLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-BasicLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-MathLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-MotionControlLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-NeuronLifeLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-PhysLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-PulseClassicModelsLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-PulseLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-PulseNeuronLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-ReceiverLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-SensorLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lNmsdk-SourceLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Win/Lib.Qt/ -lcurl.qt
} else:unix {
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lrdk.static.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lRdk-BasicLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lRdk-BasicStatisticLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lRdk-IoLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lRdk-SourcesLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-ActLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-BasicLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-MathLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-MotionControlLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-NeuronLifeLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-PhysLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-PulseClassicModelsLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-PulseLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-PulseNeuronLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-ReceiverLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-SensorLib.qt
 LIBS += -L$$PWD/../../../Bin/Platform/Linux/Lib.Qt/ -lNmsdk-SourceLib.qt
}

#including boost
windows {
 INCLUDEPATH += $$(BOOST_PATH)/include/boost-1_54

 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_chrono-vc100-mt-gd-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_date_time-vc100-mt-gd-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_regex-vc100-mt-gd-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_system-vc100-mt-gd-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_thread-vc100-mt-gd-1_54.lib

 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_chrono-vc100-mt-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_date_time-vc100-mt-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_regex-vc100-mt-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_system-vc100-mt-1_54.lib
 LIBS += $$(BOOST_PATH)/lib32-msvc-10.0/libboost_thread-vc100-mt-1_54.lib

 #LIBS += $$(BOOST_PATH)/lib/libboost_atomic-vc100-mt-gd-1_54.lib
 #LIBS += $$(BOOST_PATH)/lib/libboost_signals-vc100-mt-gd-1_54.lib
 #LIBS += $$(BOOST_PATH)/lib/libboost_timer-vc100-mt-gd-1_54.lib

 #LIBS += $$(BOOST_PATH)/lib/libboost_atomic-vc100-mt-1_54.lib
 #LIBS += $$(BOOST_PATH)/lib/libboost_signals-vc100-mt-1_54.lib
 #LIBS += $$(BOOST_PATH)/lib/libboost_timer-vc100-mt-1_54.lib
} else:unix {
 LIBS += -lboost_thread
 LIBS += -lboost_system
 LIBS += -lpthread
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
    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.cpp

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
    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.h

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
    ../../../Rdk/GUI/Qt/UCreateConfigurationWizardWidget.ui
