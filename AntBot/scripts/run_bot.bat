@echo off

mkdir "%~dp0..\..\tools\bots"

move "%~dp0..\bin\x64\Release\AntBot.exe" "%~dp0..\..\tools\bots"

cd "%~dp0..\..\tools"

cmd /k "play_one_game_mybot.cmd"

exit