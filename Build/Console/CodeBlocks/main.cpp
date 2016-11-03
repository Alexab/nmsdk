#include <iostream>
#include "../../../Rdk/Deploy/Include/rdk_cpp_initlib.h"
#include "../../../Rdk/Core/Application/UApplication.h"
#include <boost/program_options/cmdline.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>

using namespace std;

namespace po = boost::program_options;

po::options_description CmdLineDescription("Allowed options");
po::variables_map CmdVariablesMap;

std::string Version("0.2");
//std::map<std::string,std::string> ParsedArgs;

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

void InitCmdParser(void)
{
 CmdLineDescription.add_options()
    ("help", "produce help message")
    ("conf", po::value<string>(), "Configuration file name")
    ("ctime", po::value<double>(), "Calculation time interval, in seconds")
;
}

int main(int argc, char* argv[])
{
 InitCmdParser();

 po::store(po::parse_command_line(argc, argv, CmdLineDescription), CmdVariablesMap);
 po::notify(CmdVariablesMap);

 if (CmdVariablesMap.count("help"))
 {
  cout << CmdLineDescription << "\n";
  return 1;
 }

 int res(RDK_SUCCESS);

 cout << "NMSDK console version "<<Version<<endl;

 std::string configuration_name;
 double calc_time_interval(0.0);
 if (CmdVariablesMap.count("conf"))
 {
  configuration_name = CmdVariablesMap["conf"].as<std::string>();
 }
 else
 {
  cout<<"Configuration name is empty or doesn't set!"<<endl;
  return 9000003;
 }

 if(CmdVariablesMap.count("ctime"))
 {
  calc_time_interval = CmdVariablesMap["ctime"].as<double>();
 }

 if(calc_time_interval<=0 || calc_time_interval>10e8)
 {
  cout<<"CalcTimeInterval: Incorrect value "<<calc_time_interval<<"!"<<endl;
  return 9000004;
 }
 cout<<"CalcTimeInterval: "<<calc_time_interval<<" sec"<<endl;

 res=RdkApplicationInit(argv[0]);
 if(res != RDK_SUCCESS)
 {
  cout<<"Init: Fail!"<<endl;
  return res;
 }
 cout<<"Init: Success."<<endl;

 // Loading configuration
 bool open_res=RdkApplication.OpenProject(configuration_name);
 GetEnvironmentLock(0)->SetMaxCalcTime(calc_time_interval);
 if(open_res != true)
 {
  cout<<"Open configuration: Fail!"<<endl;
  return res;
 }
 cout<<"Open configuration: Success."<<endl;
 cout<<"Ready to calc."<<endl;


 RdkApplication.StartChannel(0);
 double calc_time(0.0);
 while(!GetEnvironmentLock(0)->IsCalcFinished())
 {
  calc_time=GetModelLock(0)->GetTime().GetDoubleTime();
  cout<<"Model time: "<<calc_time<<endl;
  RDK::Sleep(1);
//  if(calc_time>=calc_time_interval)
//   break;
 }
 calc_time=GetModelLock(0)->GetTime().GetDoubleTime();
 cout<<"Model time: "<<calc_time<<endl;
 RdkApplication.PauseChannel(0);
 RDK::Sleep(100);
 MCore_ChannelUnInit(0);
 return 0;
}
