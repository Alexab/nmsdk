mkdir InstallSources
xcopy "..\..\Bin\Platform\Win\*.exe" InstallSources\Bin\Platform\Win\ /Y /D
xcopy "..\..\Bin\Platform\Win\*.dll" InstallSources\Bin\Platform\Win\ /Y /D
xcopy "..\..\Bin\Platform\Win\*.ini" InstallSources\Bin\Platform\Win\ /Y /D
xcopy "..\..\Bin\Platform\Win\Fonts\*.*" InstallSources\Bin\Platform\Win\Fonts\ /Y /D
xcopy "..\..\Bin\Configs\MC-RCN\*.*" InstallSources\Bin\Configs\MC-RCN\*.* /Y /E /D
rem rmdir /Q /S InstallSources\Bin\Configs\MC-RCN\ImageLog
rem rmdir /Q /S InstallSources\Bin\Configs\MC-RCN\EventsLog
