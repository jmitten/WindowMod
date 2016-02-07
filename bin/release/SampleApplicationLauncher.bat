@ECHO OFF

REM BEGIN VARIABLES

SET winmod_ProgramPath=Notepad
SET winmod_WindowModPath="WindowMod.exe"
SET winmod_WindowTitle="Untitled - Notepad"
SET winmod_NewWindowTitle="WindowMod"
SET /A winmod_HideTerminal=0
SET /A winmod_TimeOutValue=120

REM END VARIABLES

start %winmod_ProgramPath%

IF /I "%winmod_HideTerminal%" EQU "1" (
	start "" %winmod_WindowModPath% -t %winmod_TimeOutValue% -w %winmod_WindowTitle% -r %winmod_NewWindowTitle% -f
) ELSE (
	start "" %winmod_WindowModPath% -t %winmod_TimeOutValue% -w %winmod_WindowTitle% -r %winmod_NewWindowTitle%
)


