#include <QApplication>
#include <QMessageBox>

#include "UGEngineControllWidget.h"
#include "../../../../Rdk/Core/Utilities/UIniFile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // сложна€ null инициализаци€

    /// Ёкзепл€р прототипа декодера команд
    RDK::URpcDecoderInternal rpcDecoder;

    /// Ёкзепл€р класса диспетчера команд
    RDK::URpcDispatcher rpcDispatcher;


    /// Ёкземпл€р класса контроллера сервера
    RDK::UServerControl serverControl;
    RDK::URpcDecoderCommon rpcDecoderCommon;

    /// Ёкземпл€р класса контроллера расчета
    UEngineControlQt engineControl;

    /// Ёкзепл€р класса проекта
    RDK::UProject project;

    /// Ёкзепл€р класса приложени€
    RDK::UApplication application;

    /// Ёкземпл€р класса менеджера тестов
    RDK::UTestManager rdkTestManager;

    rdkTestManager.SetApplication(&application);

    rpcDispatcher.SetDecoderPrototype(&rpcDecoder);
    rpcDispatcher.SetCommonDecoder(&rpcDecoderCommon);

    application.SetApplicationFileName(QApplication::applicationFilePath().toLocal8Bit().constData());
    application.SetRpcDispatcher(&rpcDispatcher);
    application.SetServerControl(&serverControl);
    application.SetEngineControl(&engineControl);
    application.SetProject(&project);
    application.SetLogDir((QApplication::applicationDirPath()+"/").toLocal8Bit().constData());
    application.SetDebugMode(true);
    application.SetTestManager(&rdkTestManager);

    if(argc > 1)
      application.ProcessCommandLineArgs(argc, argv);

    application.Init();

    if(application.IsTestMode())
    {
      bool closeAfterTests = false;
      int returnCode = application.Test(closeAfterTests);
      if(closeAfterTests)
        return returnCode;
    }

    // »нициализаци€ из стартового ini файла
    RDK::UIniFile<char> projectIniFile;
    projectIniFile.LoadFromFile("NeuroModeler.ini");
    std::string startProjectName = projectIniFile("General", "AutoexecProjectFileName", "");
    int autoStartProjectFlag = atoi(projectIniFile("General", "autoStartProjectFlag", "").c_str());
    int hideAdminForm        = atoi(projectIniFile("General", "HideAdminForm", "").c_str());
    int startMinimized       = atoi(projectIniFile("General", "StartMinimized", "").c_str());

    UGEngineControllWidget w(NULL, &application);

    if(!startProjectName.empty())
     application.OpenProject(startProjectName);
    RDK::UIVisualControllerStorage::UpdateInterface(true);

    if(hideAdminForm)
      w.hide();
    else
      w.show();

    if(autoStartProjectFlag)
    {
      try
      {
        if(!application.GetProjectOpenFlag())
            return -1;

        application.StartChannel(-1);
      }
      catch(RDK::UException& e)
      {
        QMessageBox::critical(&w ,"UError at start calculation", QString(e.what()), QMessageBox::Ok);
      }
      catch(std::exception& e)
      {
        QMessageBox::critical(&w ,"Error at start calculation", QString(e.what()), QMessageBox::Ok);
      }
    }

    if(startMinimized)
      w.showMinimized();

    return a.exec();
}
