# Microsoft Developer Studio Generated NMAKE File, Format Version 4.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

!IF "$(CFG)" == ""
CFG=Ecs - Win32 Debug
!MESSAGE No configuration specified.  Defaulting to Ecs - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Ecs - Win32 Release" && "$(CFG)" != "Ecs - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE on this makefile
!MESSAGE by defining the macro CFG on the command line.  For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ecs.mak" CFG="Ecs - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ecs - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ecs - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 
################################################################################
# Begin Project
# PROP Target_Last_Scanned "Ecs - Win32 Debug"
CPP=cl.exe
MTL=mktyplib.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ecs - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
OUTDIR=.\..\Bin
INTDIR=.\Release

ALL : "$(OUTDIR)\Ecs.exe"

CLEAN : 
	-@erase "..\Bin\Ecs.exe"
	-@erase ".\Release\EcsDoc.obj"
	-@erase ".\Release\Ecs.pch"
	-@erase ".\Release\StackerInfo.obj"
	-@erase ".\Release\Job.obj"
	-@erase ".\Release\ConfigDlg.obj"
	-@erase ".\Release\LogDlg.obj"
	-@erase ".\Release\CvThread.obj"
	-@erase ".\Release\ManualDlg.obj"
	-@erase ".\Release\Lib.obj"
	-@erase ".\Release\Serial.obj"
	-@erase ".\Release\LogoDlg.obj"
	-@erase ".\Release\Config.obj"
	-@erase ".\Release\ScThread.obj"
	-@erase ".\Release\control.obj"
	-@erase ".\Release\log.obj"
	-@erase ".\Release\StackerDlg.obj"
	-@erase ".\Release\JobItemDlg.obj"
	-@erase ".\Release\plc.obj"
	-@erase ".\Release\StdAfx.obj"
	-@erase ".\Release\EcsView.obj"
	-@erase ".\Release\ConveyorTrackInfo.obj"
	-@erase ".\Release\DispThread.obj"
	-@erase ".\Release\ConveyorDlg.obj"
	-@erase ".\Release\OpBoxDlg.obj"
	-@erase ".\Release\Host.obj"
	-@erase ".\Release\JobDlg.obj"
	-@erase ".\Release\MainFrm.obj"
	-@erase ".\Release\Ecs.obj"
	-@erase ".\Release\Ecs.res"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ecs.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/" /c 
CPP_OBJS=.\Release/
CPP_SBRS=
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /win32
MTL_PROJ=/nologo /D "NDEBUG" /win32 
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x412 /fo"$(INTDIR)/Ecs.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ecs.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)/Ecs.pdb" /machine:I386 /out:"$(OUTDIR)/Ecs.exe" 
LINK32_OBJS= \
	"$(INTDIR)/EcsDoc.obj" \
	"$(INTDIR)/StackerInfo.obj" \
	"$(INTDIR)/Job.obj" \
	"$(INTDIR)/ConfigDlg.obj" \
	"$(INTDIR)/LogDlg.obj" \
	"$(INTDIR)/CvThread.obj" \
	"$(INTDIR)/ManualDlg.obj" \
	"$(INTDIR)/Lib.obj" \
	"$(INTDIR)/Serial.obj" \
	"$(INTDIR)/LogoDlg.obj" \
	"$(INTDIR)/Config.obj" \
	"$(INTDIR)/ScThread.obj" \
	"$(INTDIR)/control.obj" \
	"$(INTDIR)/log.obj" \
	"$(INTDIR)/StackerDlg.obj" \
	"$(INTDIR)/JobItemDlg.obj" \
	"$(INTDIR)/plc.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/EcsView.obj" \
	"$(INTDIR)/ConveyorTrackInfo.obj" \
	"$(INTDIR)/DispThread.obj" \
	"$(INTDIR)/ConveyorDlg.obj" \
	"$(INTDIR)/OpBoxDlg.obj" \
	"$(INTDIR)/Host.obj" \
	"$(INTDIR)/JobDlg.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/Ecs.obj" \
	"$(INTDIR)/Ecs.res"

"$(OUTDIR)\Ecs.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
OUTDIR=.\..\Bin
INTDIR=.\Debug

ALL : "$(OUTDIR)\Ecs.exe"

CLEAN : 
	-@erase ".\Debug\vc40.pdb"
	-@erase ".\Debug\Ecs.pch"
	-@erase ".\Debug\vc40.idb"
	-@erase "..\Bin\Ecs.exe"
	-@erase ".\Debug\EcsView.obj"
	-@erase ".\Debug\ConfigDlg.obj"
	-@erase ".\Debug\JobDlg.obj"
	-@erase ".\Debug\Host.obj"
	-@erase ".\Debug\ManualDlg.obj"
	-@erase ".\Debug\DispThread.obj"
	-@erase ".\Debug\ConveyorTrackInfo.obj"
	-@erase ".\Debug\EcsDoc.obj"
	-@erase ".\Debug\LogDlg.obj"
	-@erase ".\Debug\ConveyorDlg.obj"
	-@erase ".\Debug\Ecs.obj"
	-@erase ".\Debug\Serial.obj"
	-@erase ".\Debug\ScThread.obj"
	-@erase ".\Debug\Config.obj"
	-@erase ".\Debug\Job.obj"
	-@erase ".\Debug\StackerInfo.obj"
	-@erase ".\Debug\MainFrm.obj"
	-@erase ".\Debug\plc.obj"
	-@erase ".\Debug\CvThread.obj"
	-@erase ".\Debug\Lib.obj"
	-@erase ".\Debug\control.obj"
	-@erase ".\Debug\StackerDlg.obj"
	-@erase ".\Debug\log.obj"
	-@erase ".\Debug\OpBoxDlg.obj"
	-@erase ".\Debug\StdAfx.obj"
	-@erase ".\Debug\JobItemDlg.obj"
	-@erase ".\Debug\LogoDlg.obj"
	-@erase ".\Debug\Ecs.res"
	-@erase "..\Bin\Ecs.ilk"
	-@erase "..\Bin\Ecs.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ecs.pch" /Yu"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c 
CPP_OBJS=.\Debug/
CPP_SBRS=
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /win32
MTL_PROJ=/nologo /D "_DEBUG" /win32 
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
RSC_PROJ=/l 0x412 /fo"$(INTDIR)/Ecs.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
BSC32_FLAGS=/nologo /o"$(OUTDIR)/Ecs.bsc" 
BSC32_SBRS=
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)/Ecs.pdb" /debug /machine:I386 /out:"$(OUTDIR)/Ecs.exe" 
LINK32_OBJS= \
	"$(INTDIR)/EcsView.obj" \
	"$(INTDIR)/ConfigDlg.obj" \
	"$(INTDIR)/JobDlg.obj" \
	"$(INTDIR)/Host.obj" \
	"$(INTDIR)/ManualDlg.obj" \
	"$(INTDIR)/DispThread.obj" \
	"$(INTDIR)/ConveyorTrackInfo.obj" \
	"$(INTDIR)/EcsDoc.obj" \
	"$(INTDIR)/LogDlg.obj" \
	"$(INTDIR)/ConveyorDlg.obj" \
	"$(INTDIR)/Ecs.obj" \
	"$(INTDIR)/Serial.obj" \
	"$(INTDIR)/ScThread.obj" \
	"$(INTDIR)/Config.obj" \
	"$(INTDIR)/Job.obj" \
	"$(INTDIR)/StackerInfo.obj" \
	"$(INTDIR)/MainFrm.obj" \
	"$(INTDIR)/plc.obj" \
	"$(INTDIR)/CvThread.obj" \
	"$(INTDIR)/Lib.obj" \
	"$(INTDIR)/control.obj" \
	"$(INTDIR)/StackerDlg.obj" \
	"$(INTDIR)/log.obj" \
	"$(INTDIR)/OpBoxDlg.obj" \
	"$(INTDIR)/StdAfx.obj" \
	"$(INTDIR)/JobItemDlg.obj" \
	"$(INTDIR)/LogoDlg.obj" \
	"$(INTDIR)/Ecs.res"

"$(OUTDIR)\Ecs.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_OBJS)}.obj:
   $(CPP) $(CPP_PROJ) $<  

.c{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cpp{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

.cxx{$(CPP_SBRS)}.sbr:
   $(CPP) $(CPP_PROJ) $<  

################################################################################
# Begin Target

# Name "Ecs - Win32 Release"
# Name "Ecs - Win32 Debug"

!IF  "$(CFG)" == "Ecs - Win32 Release"

!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

!ENDIF 

################################################################################
# Begin Source File

SOURCE=.\ReadMe.txt

!IF  "$(CFG)" == "Ecs - Win32 Release"

!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ecs.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_ECS_C=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\MainFrm.h"\
	".\EcsDoc.h"\
	".\EcsView.h"\
	".\LogoDlg.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	".\ConveyorDlg.h"\
	

"$(INTDIR)\Ecs.obj" : $(SOURCE) $(DEP_CPP_ECS_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_ECS_C=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\MainFrm.h"\
	".\EcsDoc.h"\
	".\EcsView.h"\
	".\LogoDlg.h"\
	".\Host.h"\
	".\ConveyorDlg.h"\
	".\Thread.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\Ecs.obj" : $(SOURCE) $(DEP_CPP_ECS_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "Ecs - Win32 Release"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D\
 "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ecs.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/" /c\
 $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ecs.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

# ADD CPP /Yc"stdafx.h"

BuildCmds= \
	$(CPP) /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)/Ecs.pch" /Yc"stdafx.h" /Fo"$(INTDIR)/"\
 /Fd"$(INTDIR)/" /c $(SOURCE) \
	

"$(INTDIR)\StdAfx.obj" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

"$(INTDIR)\Ecs.pch" : $(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
   $(BuildCmds)

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MainFrm.cpp
DEP_CPP_MAINF=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\MainFrm.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\EcsDoc.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_ECSDO=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Thread.h"\
	".\Log.h"\
	".\LogDlg.h"\
	".\ManualDlg.h"\
	".\JobDlg.h"\
	".\ConfigDlg.h"\
	".\MainFrm.h"\
	".\LogoDlg.h"\
	".\Host.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\EcsDoc.obj" : $(SOURCE) $(DEP_CPP_ECSDO) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_ECSDO=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Thread.h"\
	".\Log.h"\
	".\LogDlg.h"\
	".\ManualDlg.h"\
	".\JobDlg.h"\
	".\ConfigDlg.h"\
	".\MainFrm.h"\
	".\LogoDlg.h"\
	".\Host.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	".\Config.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\EcsDoc.obj" : $(SOURCE) $(DEP_CPP_ECSDO) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\EcsView.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_ECSVI=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\EcsView.h"\
	".\MainFrm.h"\
	".\Control.h"\
	".\StackerDlg.h"\
	".\OpBoxDlg.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	".\ConveyorDlg.h"\
	

"$(INTDIR)\EcsView.obj" : $(SOURCE) $(DEP_CPP_ECSVI) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_ECSVI=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\EcsView.h"\
	".\MainFrm.h"\
	".\Control.h"\
	".\StackerDlg.h"\
	".\OpBoxDlg.h"\
	".\Host.h"\
	".\ConveyorDlg.h"\
	".\Thread.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\EcsView.obj" : $(SOURCE) $(DEP_CPP_ECSVI) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Ecs.rc
DEP_RSC_ECS_R=\
	".\res\Ecs.ico"\
	".\RES\Net09a.ico"\
	".\RES\Trffc10a.ico"\
	".\RES\Trffc10b.ico"\
	".\RES\Trffc10c.ico"\
	".\RES\Net09b.ico"\
	".\RES\TRACK.ico"\
	".\RES\Knife.ico"\
	".\RES\Bug.ico"\
	".\RES\Tool5.ico"\
	".\RES\EXIT.ico"\
	".\RES\Wxtfile.ico"\
	".\RES\ecslogo.bmp"\
	".\res\EcsDoc.ico"\
	".\RES\Enroll.ico"\
	".\RES\Pass.ico"\
	".\RES\Return.ico"\
	".\res\Toolbar.bmp"\
	".\res\Ecs.rc2"\
	

"$(INTDIR)\Ecs.res" : $(SOURCE) $(DEP_RSC_ECS_R) "$(INTDIR)"
   $(RSC) $(RSC_PROJ) $(SOURCE)


# End Source File
################################################################################
# Begin Source File

SOURCE=.\control.cpp
DEP_CPP_CONTR=\
	".\StdAfx.h"\
	".\Control.h"\
	

"$(INTDIR)\control.obj" : $(SOURCE) $(DEP_CPP_CONTR) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Job.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_JOB_C=\
	".\StdAfx.h"\
	".\Job.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	

"$(INTDIR)\Job.obj" : $(SOURCE) $(DEP_CPP_JOB_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_JOB_C=\
	".\StdAfx.h"\
	".\Job.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\Job.obj" : $(SOURCE) $(DEP_CPP_JOB_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Serial.cpp
DEP_CPP_SERIA=\
	".\StdAfx.h"\
	".\Serial.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\Serial.obj" : $(SOURCE) $(DEP_CPP_SERIA) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\plc.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_PLC_C=\
	".\StdAfx.h"\
	".\Plc.h"\
	".\Lib.h"\
	".\Serial.h"\
	".\Thread.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	

"$(INTDIR)\plc.obj" : $(SOURCE) $(DEP_CPP_PLC_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_PLC_C=\
	".\StdAfx.h"\
	".\Plc.h"\
	".\Lib.h"\
	".\Serial.h"\
	".\Thread.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\plc.obj" : $(SOURCE) $(DEP_CPP_PLC_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\log.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_LOG_C=\
	".\StdAfx.h"\
	".\Log.h"\
	".\EcsDoc.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\log.obj" : $(SOURCE) $(DEP_CPP_LOG_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_LOG_C=\
	".\StdAfx.h"\
	".\Log.h"\
	".\EcsDoc.h"\
	".\Host.h"\
	

"$(INTDIR)\log.obj" : $(SOURCE) $(DEP_CPP_LOG_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Config.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_CONFI=\
	".\StdAfx.h"\
	".\Config.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	

"$(INTDIR)\Config.obj" : $(SOURCE) $(DEP_CPP_CONFI) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_CONFI=\
	".\StdAfx.h"\
	".\Config.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\Config.obj" : $(SOURCE) $(DEP_CPP_CONFI) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LogDlg.cpp
DEP_CPP_LOGDL=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\Log.h"\
	".\LogDlg.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\LogDlg.obj" : $(SOURCE) $(DEP_CPP_LOGDL) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\ManualDlg.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_MANUA=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\ManualDlg.h"\
	".\EcsDoc.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\ManualDlg.obj" : $(SOURCE) $(DEP_CPP_MANUA) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_MANUA=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\ManualDlg.h"\
	".\EcsDoc.h"\
	".\Host.h"\
	

"$(INTDIR)\ManualDlg.obj" : $(SOURCE) $(DEP_CPP_MANUA) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JobDlg.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_JOBDL=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\Job.h"\
	".\JobDlg.h"\
	".\JobItemDlg.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	

"$(INTDIR)\JobDlg.obj" : $(SOURCE) $(DEP_CPP_JOBDL) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_JOBDL=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\Job.h"\
	".\JobDlg.h"\
	".\JobItemDlg.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\JobDlg.obj" : $(SOURCE) $(DEP_CPP_JOBDL) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConfigDlg.cpp
DEP_CPP_CONFIG=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\ConfigDlg.h"\
	".\Config.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\ConfigDlg.obj" : $(SOURCE) $(DEP_CPP_CONFIG) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\CvThread.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_CVTHR=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Serial.h"\
	".\Plc.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Host.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\CvThread.obj" : $(SOURCE) $(DEP_CPP_CVTHR) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_CVTHR=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Serial.h"\
	".\Plc.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Host.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\CvThread.obj" : $(SOURCE) $(DEP_CPP_CVTHR) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ScThread.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_SCTHR=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Serial.h"\
	".\Plc.h"\
	".\Thread.h"\
	".\Host.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\ScThread.obj" : $(SOURCE) $(DEP_CPP_SCTHR) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_SCTHR=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Serial.h"\
	".\Plc.h"\
	".\Thread.h"\
	".\Host.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\ScThread.obj" : $(SOURCE) $(DEP_CPP_SCTHR) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\StackerDlg.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_STACK=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\StackerDlg.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	

"$(INTDIR)\StackerDlg.obj" : $(SOURCE) $(DEP_CPP_STACK) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_STACK=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\StackerDlg.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\StackerDlg.obj" : $(SOURCE) $(DEP_CPP_STACK) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConveyorDlg.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_CONVE=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\ConveyorDlg.h"\
	".\EcsDoc.h"\
	".\ManualDlg.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\ConveyorDlg.obj" : $(SOURCE) $(DEP_CPP_CONVE) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_CONVE=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\ConveyorDlg.h"\
	".\EcsDoc.h"\
	".\ManualDlg.h"\
	".\Thread.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\ConveyorDlg.obj" : $(SOURCE) $(DEP_CPP_CONVE) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\JobItemDlg.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_JOBIT=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\Job.h"\
	".\JobItemDlg.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	

"$(INTDIR)\JobItemDlg.obj" : $(SOURCE) $(DEP_CPP_JOBIT) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_JOBIT=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\Job.h"\
	".\JobItemDlg.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\JobItemDlg.obj" : $(SOURCE) $(DEP_CPP_JOBIT) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\MakeHelp.bat

!IF  "$(CFG)" == "Ecs - Win32 Release"

!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\OpBoxDlg.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_OPBOX=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\OpBoxDlg.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\OpBoxDlg.obj" : $(SOURCE) $(DEP_CPP_OPBOX) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_OPBOX=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\OpBoxDlg.h"\
	".\Host.h"\
	

"$(INTDIR)\OpBoxDlg.obj" : $(SOURCE) $(DEP_CPP_OPBOX) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\LogoDlg.cpp
DEP_CPP_LOGOD=\
	".\StdAfx.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Ecs.h"\
	".\LogoDlg.h"\
	

"$(INTDIR)\LogoDlg.obj" : $(SOURCE) $(DEP_CPP_LOGOD) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\Hlp\Ecs.hpj

!IF  "$(CFG)" == "Ecs - Win32 Release"

!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\ConveyorTrackInfo.cpp
DEP_CPP_CONVEY=\
	".\StdAfx.h"\
	".\ConveyorTrackInfo.h"\
	

"$(INTDIR)\ConveyorTrackInfo.obj" : $(SOURCE) $(DEP_CPP_CONVEY) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
################################################################################
# Begin Source File

SOURCE=.\StackerInfo.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_STACKE=\
	".\StdAfx.h"\
	".\StackerInfo.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	

"$(INTDIR)\StackerInfo.obj" : $(SOURCE) $(DEP_CPP_STACKE) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_STACKE=\
	".\StdAfx.h"\
	".\StackerInfo.h"\
	".\EcsDoc.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Host.h"\
	

"$(INTDIR)\StackerInfo.obj" : $(SOURCE) $(DEP_CPP_STACKE) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Host.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_HOST_=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\Host.h"\
	".\EcsDoc.h"\
	".\Plc.h"\
	".\MainFrm.h"\
	".\Lib.h"\
	{$(INCLUDE)}"\Define.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	".\Serial.h"\
	

"$(INTDIR)\Host.obj" : $(SOURCE) $(DEP_CPP_HOST_) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_HOST_=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\Host.h"\
	".\EcsDoc.h"\
	".\Plc.h"\
	".\MainFrm.h"\
	".\Lib.h"\
	".\Serial.h"\
	".\Thread.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\Host.obj" : $(SOURCE) $(DEP_CPP_HOST_) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\DispThread.cpp

!IF  "$(CFG)" == "Ecs - Win32 Release"

DEP_CPP_DISPT=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Serial.h"\
	".\Plc.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Host.h"\
	".\Job.h"\
	".\Config.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\DispThread.obj" : $(SOURCE) $(DEP_CPP_DISPT) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

DEP_CPP_DISPT=\
	".\StdAfx.h"\
	".\Ecs.h"\
	".\EcsDoc.h"\
	".\Serial.h"\
	".\Plc.h"\
	".\Thread.h"\
	".\Log.h"\
	".\Host.h"\
	".\ConveyorTrackInfo.h"\
	".\StackerInfo.h"\
	{$(INCLUDE)}"\Define.h"\
	

"$(INTDIR)\DispThread.obj" : $(SOURCE) $(DEP_CPP_DISPT) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


!ENDIF 

# End Source File
################################################################################
# Begin Source File

SOURCE=.\Lib.cpp
DEP_CPP_LIB_C=\
	".\StdAfx.h"\
	".\Lib.h"\
	

"$(INTDIR)\Lib.obj" : $(SOURCE) $(DEP_CPP_LIB_C) "$(INTDIR)"\
 "$(INTDIR)\Ecs.pch"


# End Source File
# End Target
# End Project
################################################################################
