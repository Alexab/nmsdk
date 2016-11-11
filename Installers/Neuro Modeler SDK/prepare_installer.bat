mkdir InstallSources
xcopy "..\..\Bin\Platform\Win\*.exe" InstallSources\Bin\Platform\Win\ /Y /D
xcopy "..\..\Bin\Platform\Win\*.dll" InstallSources\Bin\Platform\Win\ /Y /D
xcopy "..\..\Bin\Platform\Win\*.ini" InstallSources\Bin\Platform\Win\ /Y /D
xcopy "..\..\Bin\Platform\Win\Fonts\*.*" InstallSources\Bin\Platform\Win\Fonts\ /Y /D
xcopy "..\..\Bin\Configs\MC-RCN\*.*" InstallSources\Bin\Configs\MC-RCN\*.* /Y /E /D
xcopy "..\..\Bin\Configs\NM-Neurons\*.*" InstallSources\Bin\Configs\NM-Neurons\*.* /Y /E /D
xcopy "..\..\Bin\Configs\MC-Muscles\*.*" InstallSources\Bin\Configs\MC-Muscles\*.* /Y /E /D
xcopy "..\..\Docs\NMSDK.NeuronModel.ConfigurationSamples.Ru.doc" InstallSources\Docs\NMSDK.NeuronModel.ConfigurationSamples.Ru.doc /Y /D
xcopy "..\..\Docs\NMSDK.NeuronModel.Ru.doc" InstallSources\Docs\NMSDK.NeuronModel.Ru.doc /Y /D
xcopy "..\..\Rdk\Docs\RDK.GuiDescription.Bcb.Ru.doc" InstallSources\Docs\RDK.GuiDescription.Bcb.Ru.doc /Y /D
xcopy "..\..\Rdk\Docs\RDK.RuntimeConfigurationDescription.Ru.doc" InstallSources\Docs\RDK.RuntimeConfigurationDescription.Ru.doc /Y /D
rem rmdir /Q /S InstallSources\Bin\Configs\MC-RCN\ImageLog
rem rmdir /Q /S InstallSources\Bin\Configs\MC-RCN\EventsLog
rem rmdir /Q /S InstallSources\Bin\Configs\NM-Neurons\ImageLog
rem rmdir /Q /S InstallSources\Bin\Configs\NM-Neurons\EventsLog
rem rmdir /Q /S InstallSources\Bin\Configs\MC-Muscles\ImageLog
rem rmdir /Q /S InstallSources\Bin\Configs\MC-Muscles\EventsLog
