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

    // »нициализаци€ из стартового ini файла
    RDK::UIniFile<char> projectIniFile;
    projectIniFile.LoadFromFile("VideoAnalytics.ini");
    std::string startProjectName = projectIniFile("General", "AutoexecProjectFileName", "");
    int autoStartProjectFlag = atoi(projectIniFile("General", "autoStartProjectFlag", "0").c_str());
    int hideAdminForm        = atoi(projectIniFile("General", "HideAdminForm", "0").c_str());
    int startMinimized       = atoi(projectIniFile("General", "StartMinimized", "0").c_str());

    std::string mainFormName=projectIniFile("General", "MainFormName", "");
    int minimizeToTray=atoi(projectIniFile("General","MinimizeToTray","0").c_str());
    std::string programName=projectIniFile("General","ProgramName","Server");
    std::string configsMainPath=projectIniFile("General", "ConfigsMainPath", "../../../Configs/");
    int neverSleepOnMMThreadContention=atoi(projectIniFile("General","NeverSleepOnMMThreadContention","0").c_str());
    std::string logDir=projectIniFile("Log","Dir","");
    int startupDelay=atoi(projectIniFile("General","StartupDelay","0").c_str());

    int useNewXmlFormatProjectFile=atoi(projectIniFile("General","UseNewXmlFormatProjectFile","0").c_str());
    int useNewProjectFilesStructure=atoi(projectIniFile("General","UseNewProjectFilesStructure","0").c_str());

    if(startupDelay>0)
    {
     RDK::Sleep(startupDelay);
    }

    int logDebugMode=atoi(projectIniFile("Log","DebugMode","1").c_str());

    int disableAdminForm=atoi(projectIniFile("General","DisableAdminForm","0").c_str());


    rdkTestManager.SetApplication(&application);

    rpcDispatcher.SetDecoderPrototype(&rpcDecoder);
    rpcDispatcher.SetCommonDecoder(&rpcDecoderCommon);

    application.SetRpcDispatcher(&rpcDispatcher);
    application.SetServerControl(&serverControl);
    application.SetEngineControl(&engineControl);
    application.SetProject(&project);

    application.SetApplicationFileName(QApplication::applicationFilePath().toLocal8Bit().constData());
    std::string log_dir_path;
    if(logDir.empty())
     log_dir_path=(QApplication::applicationDirPath()+"/EventsLog/").toLocal8Bit().constData();
    else
     log_dir_path=logDir;

    RDK::CreateNewDirectory(log_dir_path.c_str());
    application.SetLogDir(log_dir_path);

    application.SetDebugMode(logDebugMode);

    application.SetConfigsMainPath(configsMainPath);
    application.ChangeUseNewXmlFormatProjectFile(useNewXmlFormatProjectFile);
    application.ChangeUseNewProjectFilesStructure(useNewProjectFilesStructure);

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
