#include <iostream>
#include "../../../Rdk/Deploy/Include/rdk_cpp_initlib.h"
#include "../../../Rdk/Core/Application/UApplication.h"

using namespace std;

std::string Version("0.1");
std::map<std::string,std::string> ParsedArgs;

/// Экзепляр прототипа декодера команд
RDK::URpcDecoderInternal RdkRpcDecoder;

/// Экзепляр класса диспетчера команд
RDK::URpcDispatcher RdkRpcDispatcher;

/// Экзепляр класса приложения
RDK::UApplication RdkApplication;

/// Экземпляр класса контроллера сервера
RDK::UServerControl RdkServerControl;
RDK::URpcDecoderCommon RdkRpcDecoderCommon;

/// Экземпляр класса контроллера расчета
RDK::UEngineControl RdkEngineControl;

/// Экзепляр класса проекта
RDK::UProject RdkProject;

int ParseArgs(int argc, char* argv[], std::map<std::string,std::string> &parsed_args)
{
 if(argc<0 || argc>100)
  return 9000001;

 parsed_args["Application"]=argv[0];
 int index=1;
 for(int i=1;i<argc-1;i++)
 {
  parsed_args[argv[i]]=argv[i+1];
  index+=2;
 }

 return RDK_SUCCESS;
}

int RdkApplicationInit(const std::string &application_name)
{
 RdkApplication.SetApplicationFileName(application_name);
 // Грузим настройки приложения
 std::string opt_name=RDK::extract_file_name(application_name);
 if(opt_name.size()>4)
 opt_name=opt_name.substr(0,opt_name.size()-4);
// TMemIniFile *app_ini=new TMemIniFile(opt_name+".ini");
// MainFormName=app_ini->ReadString("General", "MainFormName", Name);
// HideAdminFormFlag=app_ini->ReadBool("General", "HideAdminForm", false);
// AutoexecProjectFileName=app_ini->ReadString("General", "AutoexecProjectFileName", "");
// AutoStartProjectFlag=app_ini->ReadBool("General", "AutoStartProjectFlag", false);
// VideoGrabberLicenseString=app_ini->ReadString("General","VideoGrabberLicenseString","");
// MinimizeToTray=app_ini->ReadBool("General","MinimizeToTray",false);
// StartMinimized=app_ini->ReadBool("General","StartMinimized",false);
// ProgramName=app_ini->ReadString("General","ProgramName","Server");
// LogDir=app_ini->ReadString("Log","Dir","");
// if(LogDir.Length() == 0)
//  LogDir = "EventsLog/";

// LogDebugMode=app_ini->ReadBool("Log","DebugMode",false);

// DisableAdminForm=app_ini->ReadBool("General","DisableAdminForm",false);

 RdkRpcDispatcher.SetDecoderPrototype(&RdkRpcDecoder);
 RdkRpcDispatcher.SetCommonDecoder(&RdkRpcDecoderCommon);
 RdkApplication.SetRpcDispatcher(&RdkRpcDispatcher);
 RdkApplication.SetServerControl(&RdkServerControl);
 RdkApplication.SetEngineControl(&RdkEngineControl);
 RdkApplication.SetProject(&RdkProject);
 RdkApplication.SetLogDir("EventsLog/");
 RdkApplication.SetDebugMode(true);
 if(!RdkApplication.Init())
  return 9000010;
 return RDK_SUCCESS;
}

int main(int argc, char* argv[])
{
 int res(RDK_SUCCESS);

 cout << "NMSDK console version "<<Version<<endl;
 int parse_res=ParseArgs(argc, argv,ParsedArgs);
 if(parse_res != 0)
 {
  cout<<"Argument list incorrect!"<<endl;
  return parse_res;
 }
 cout<<"Argument list have parsed successfully!"<<endl;

 res=RdkApplicationInit(ParsedArgs["Application"]);
 if(res != RDK_SUCCESS)
 {
  cout<<"Init: Fail!"<<endl;
  return res;
 }
 cout<<"Init: Success."<<endl;

 // Loading configuration
 std::string configuration_name=ParsedArgs["-p"];
 if(configuration_name.empty())
 {
  cout<<"Configuration name is empty or doesn't set!"<<endl;
  return 9000003;
 }

 res=RdkApplication.OpenProject(configuration_name);
 if(res != RDK_SUCCESS)
 {
  cout<<"Open configuration: Fail!"<<endl;
  return res;
 }
 cout<<"Open configuration: Success."<<endl;


 cout<<"Init: Passed."<<" Components in storage: "<<GetStorageLock()->GetNumClasses()<<endl;




    int a(0);
    cin>>a;
    return 0;
}
