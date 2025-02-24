# Microsoft Developer Studio Project File - Name="Ecs" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Ecs - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Ecs.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Ecs.mak" CFG="Ecs - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Ecs - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Ecs - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Ecs - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir ".\Release"
# PROP BASE Intermediate_Dir ".\Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Bin"
# PROP Intermediate_Dir ".\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Ecs - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir ".\Debug"
# PROP BASE Intermediate_Dir ".\Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x412 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# ADD LINK32 EcsLibD.lib /nologo /subsystem:windows /debug /machine:I386

!ENDIF 

# Begin Target

# Name "Ecs - Win32 Release"
# Name "Ecs - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\BufferController.cpp
# End Source File
# Begin Source File

SOURCE=.\ChangePasswordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorViewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CommonDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Config.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\control.cpp
# End Source File
# Begin Source File

SOURCE=.\Conveyor.cpp
# End Source File
# Begin Source File

SOURCE=.\ConveyorDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ConveyorTrackInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\CvLineDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CvSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\CvThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Ecs.cpp
# End Source File
# Begin Source File

SOURCE=.\Ecs.rc
# End Source File
# Begin Source File

SOURCE=.\EcsDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\EcsSockClient.cpp
# End Source File
# Begin Source File

SOURCE=.\EcsView.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\Host.cpp
# End Source File
# Begin Source File

SOURCE=.\Job.cpp
# End Source File
# Begin Source File

SOURCE=.\JobDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\JobItemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Lib.cpp
# End Source File
# Begin Source File

SOURCE=.\log.cpp
# End Source File
# Begin Source File

SOURCE=.\LogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LogoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ManualDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Melsec.cpp
# End Source File
# Begin Source File

SOURCE=.\Melsec3E.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveJob.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveJobDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MoveJobItemDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\mschart1.cpp
# End Source File
# Begin Source File

SOURCE=.\OpBoxDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PasswordDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PlcMelsec.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\RedirectionDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ResetOrderDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Rgv.cpp
# End Source File
# Begin Source File

SOURCE=.\RgvDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RgvInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\RgvManualDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\RgvThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\ScCheckDelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScErrDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScInhibitDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ScQ.cpp
# End Source File
# Begin Source File

SOURCE=.\ScQThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\ScSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ScThread.cpp
# End Source File
# Begin Source File

SOURCE=.\Serial.cpp
# End Source File
# Begin Source File

SOURCE=.\StackerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\StackerTwin.cpp
# End Source File
# Begin Source File

SOURCE=.\StackerTwinDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Statistic.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticAvailDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticBarChartDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticErrCodeDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StatisticThroughputDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ToolTipWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxis1.cpp
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle1.cpp
# End Source File
# Begin Source File

SOURCE=.\vcplot1.cpp
# End Source File
# Begin Source File

SOURCE=.\vctitle1.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\BufferController.h
# End Source File
# Begin Source File

SOURCE=.\ChangePasswordDlg.h
# End Source File
# Begin Source File

SOURCE=.\ColorViewDlg.h
# End Source File
# Begin Source File

SOURCE=.\CommonDlg.h
# End Source File
# Begin Source File

SOURCE=.\Config.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\Control.h
# End Source File
# Begin Source File

SOURCE=.\Conveyor.h
# End Source File
# Begin Source File

SOURCE=.\ConveyorDlg.h
# End Source File
# Begin Source File

SOURCE=.\ConveyorTrackInfo.h
# End Source File
# Begin Source File

SOURCE=.\CvLineDlg.h
# End Source File
# Begin Source File

SOURCE=.\CvSocket.h
# End Source File
# Begin Source File

SOURCE=.\Ecs.h
# End Source File
# Begin Source File

SOURCE=.\EcsDef.h
# End Source File
# Begin Source File

SOURCE=.\EcsDoc.h
# End Source File
# Begin Source File

SOURCE=.\EcsSockClient.h
# End Source File
# Begin Source File

SOURCE=.\EcsView.h
# End Source File
# Begin Source File

SOURCE=.\EditEx.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\Host.h
# End Source File
# Begin Source File

SOURCE=.\Info.h
# End Source File
# Begin Source File

SOURCE=.\Job.h
# End Source File
# Begin Source File

SOURCE=.\JobDlg.h
# End Source File
# Begin Source File

SOURCE=.\JobItemDlg.h
# End Source File
# Begin Source File

SOURCE=.\Lib.h
# End Source File
# Begin Source File

SOURCE=.\Log.h
# End Source File
# Begin Source File

SOURCE=.\LogDlg.h
# End Source File
# Begin Source File

SOURCE=.\LogoDlg.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ManualDlg.h
# End Source File
# Begin Source File

SOURCE=.\Melsec.h
# End Source File
# Begin Source File

SOURCE=.\Melsec3E.h
# End Source File
# Begin Source File

SOURCE=.\MoveJob.h
# End Source File
# Begin Source File

SOURCE=.\MoveJobDlg.h
# End Source File
# Begin Source File

SOURCE=.\MoveJobItemDlg.h
# End Source File
# Begin Source File

SOURCE=.\mschart1.h
# End Source File
# Begin Source File

SOURCE=.\OpBoxDlg.h
# End Source File
# Begin Source File

SOURCE=.\PasswordDlg.h
# End Source File
# Begin Source File

SOURCE=.\PlcMelsec.h
# End Source File
# Begin Source File

SOURCE=.\RedirectionDlg.h
# End Source File
# Begin Source File

SOURCE=.\ResetOrderDlg.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\Rgv.h
# End Source File
# Begin Source File

SOURCE=.\RgvDlg.h
# End Source File
# Begin Source File

SOURCE=.\RgvInfo.h
# End Source File
# Begin Source File

SOURCE=.\RgvManualDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScCheckDelDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScErrDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScInhibitDlg.h
# End Source File
# Begin Source File

SOURCE=.\ScQ.h
# End Source File
# Begin Source File

SOURCE=.\ScSocket.h
# End Source File
# Begin Source File

SOURCE=.\Serial.h
# End Source File
# Begin Source File

SOURCE=.\StackerInfo.h
# End Source File
# Begin Source File

SOURCE=.\StackerTwin.h
# End Source File
# Begin Source File

SOURCE=.\StackerTwinDlg.h
# End Source File
# Begin Source File

SOURCE=.\Statistic.h
# End Source File
# Begin Source File

SOURCE=.\StatisticAvailDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatisticBarChartDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatisticErrCodeDlg.h
# End Source File
# Begin Source File

SOURCE=.\StatisticThroughputDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SxButton.h
# End Source File
# Begin Source File

SOURCE=.\Thread.h
# End Source File
# Begin Source File

SOURCE=.\ToolTipWnd.h
# End Source File
# Begin Source File

SOURCE=.\VCAXIS.H
# End Source File
# Begin Source File

SOURCE=.\vcaxis1.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisgrid1.h
# End Source File
# Begin Source File

SOURCE=.\vcaxisscale1.h
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle.h
# End Source File
# Begin Source File

SOURCE=.\vcaxistitle1.h
# End Source File
# Begin Source File

SOURCE=.\vcbackdrop.h
# End Source File
# Begin Source File

SOURCE=.\vccategoryscale1.h
# End Source File
# Begin Source File

SOURCE=.\vcdatagrid.h
# End Source File
# Begin Source File

SOURCE=.\VCFONT1.H
# End Source File
# Begin Source File

SOURCE=.\vcfootnote.h
# End Source File
# Begin Source File

SOURCE=.\vcintersection.h
# End Source File
# Begin Source File

SOURCE=.\vclabels1.h
# End Source File
# Begin Source File

SOURCE=.\vclegend1.h
# End Source File
# Begin Source File

SOURCE=.\VCLIGHT1.H
# End Source File
# Begin Source File

SOURCE=.\vclocation.h
# End Source File
# Begin Source File

SOURCE=.\VCPEN.H
# End Source File
# Begin Source File

SOURCE=.\Vcplot.h
# End Source File
# Begin Source File

SOURCE=.\VCPLOT1.H
# End Source File
# Begin Source File

SOURCE=.\vcplotbase1.h
# End Source File
# Begin Source File

SOURCE=.\VCRECT1.H
# End Source File
# Begin Source File

SOURCE=.\vcseriescollection1.h
# End Source File
# Begin Source File

SOURCE=.\vctextlayout.h
# End Source File
# Begin Source File

SOURCE=.\VCTICK.H
# End Source File
# Begin Source File

SOURCE=.\vctitle1.h
# End Source File
# Begin Source File

SOURCE=.\vcvaluescale1.h
# End Source File
# Begin Source File

SOURCE=.\vcview3d1.h
# End Source File
# Begin Source File

SOURCE=.\VCWALL.H
# End Source File
# Begin Source File

SOURCE=.\vcweighting.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\35logo.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\35logoNew.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\35logoNew1.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\35logoV44.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\bitmap14.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\bitmap4.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\black1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\BOOKS02.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\BOOKS03.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\BOOKS04.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\BOOKS05.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\Bug.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0001.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0002.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0003.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0004.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0005.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0007.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0008.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0009.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip0010.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Clip006.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\CLIP06.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\CLIP07.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\CLIP08.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\COPY.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Ecs.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ecs.rc2
# End Source File
# Begin Source File

SOURCE=.\res\EcsDoc.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ecslogo.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\ecslogo256.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\Enroll.ico
# End Source File
# Begin Source File

SOURCE=.\RES\EXIT.ico
# End Source File
# Begin Source File

SOURCE=.\Res\glaxo.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\glaxologo.bmp
# End Source File
# Begin Source File

SOURCE=.\Res\glaxologo16.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\Res\icon6.ico
# End Source File
# Begin Source File

SOURCE=.\RES\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Icon_Complete.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Icon_Log.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_blac.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_blue.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_cyan.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_dblu.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_dcya.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_dgra.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_dgre.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_dpin.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_dred.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_dyel.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_gray.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_gree.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_pink.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_red.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_whit.ico
# End Source File
# Begin Source File

SOURCE=.\Res\idr_yell.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Knife.ico
# End Source File
# Begin Source File

SOURCE=.\Res\load1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\NET02.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\NET03.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\NET04.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\NET05.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\NET06.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\Net09a.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Net09b.ico
# End Source File
# Begin Source File

SOURCE=.\RES\NETHOOD.ICO
# End Source File
# Begin Source File

SOURCE=.\Res\no_load.ico
# End Source File
# Begin Source File

SOURCE=.\RES\NOTE03.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\NOTE04.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\Pass.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Return.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Tool5.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\TRACK.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Trffc10a.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Trffc10b.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Trffc10c.ico
# End Source File
# Begin Source File

SOURCE=.\RES\Wxtfile.ico
# End Source File
# End Group
# End Target
# End Project
# Section Ecs : {EBF97E22-731F-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcLCoor
# 	2:10:HeaderFile:vclcoor.h
# 	2:8:ImplFile:vclcoor.cpp
# End Section
# Section Ecs : {51DCC624-95B7-11CE-86B3-444553540000}
# 	2:5:Class:CVcSeriesMarker
# 	2:10:HeaderFile:vcseriesmarker.h
# 	2:8:ImplFile:vcseriesmarker.cpp
# End Section
# Section Ecs : {0AA0FE20-912A-11CE-86B3-444553540000}
# 	2:5:Class:CVcSeries
# 	2:10:HeaderFile:vcseries1.h
# 	2:8:ImplFile:vcseries1.cpp
# End Section
# Section Ecs : {EDDF9242-764B-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcLocation
# 	2:10:HeaderFile:vclocation.h
# 	2:8:ImplFile:vclocation.cpp
# End Section
# Section Ecs : {6237536A-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcAxisScale
# 	2:10:HeaderFile:vcaxisscale1.h
# 	2:8:ImplFile:vcaxisscale1.cpp
# End Section
# Section Ecs : {00D6D1A0-728C-11CF-93D5-0020AF99504A}
# 	2:5:Class:CMSChart
# 	2:10:HeaderFile:mschart1.h
# 	2:8:ImplFile:mschart1.cpp
# End Section
# Section Ecs : {9BA79C60-7403-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcColor
# 	2:10:HeaderFile:vccolor1.h
# 	2:8:ImplFile:vccolor1.cpp
# End Section
# Section Ecs : {2F6DD6A2-95E5-11CE-86B3-444553540000}
# 	2:5:Class:CVcDataPointLabel
# 	2:10:HeaderFile:vcdatapointlabel.h
# 	2:8:ImplFile:vcdatapointlabel.cpp
# End Section
# Section Ecs : {4F053F00-8396-11CE-BECC-00AA0042CB33}
# 	2:5:Class:CVcFootnote
# 	2:10:HeaderFile:vcfootnote.h
# 	2:8:ImplFile:vcfootnote.cpp
# End Section
# Section Ecs : {508D02E8-90FC-11CE-86B3-444553540000}
# 	2:5:Class:CVcWall
# 	2:10:HeaderFile:vcwall.h
# 	2:8:ImplFile:vcwall.cpp
# End Section
# Section Ecs : {6237536E-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcAxisTitle
# 	2:10:HeaderFile:vcaxistitle1.h
# 	2:8:ImplFile:vcaxistitle1.cpp
# End Section
# Section Ecs : {21645F62-90F0-11CE-86B3-444553540000}
# 	2:5:Class:CVcView3d
# 	2:10:HeaderFile:vcview3d1.h
# 	2:8:ImplFile:vcview3d1.cpp
# End Section
# Section Ecs : {AFE57020-7409-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcBrush
# 	2:10:HeaderFile:vcbrush.h
# 	2:8:ImplFile:vcbrush.cpp
# End Section
# Section Ecs : {6CB603A0-8F70-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcDataGrid
# 	2:10:HeaderFile:vcdatagrid.h
# 	2:8:ImplFile:vcdatagrid.cpp
# End Section
# Section Ecs : {95C52B60-83B1-11CE-BECC-00AA0042CB33}
# 	2:5:Class:CVcLegend
# 	2:10:HeaderFile:vclegend1.h
# 	2:8:ImplFile:vclegend1.cpp
# End Section
# Section Ecs : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section Ecs : {62375366-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcIntersection
# 	2:10:HeaderFile:vcintersection.h
# 	2:8:ImplFile:vcintersection.cpp
# End Section
# Section Ecs : {2E6A37A2-77FC-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcBackdrop
# 	2:10:HeaderFile:vcbackdrop.h
# 	2:8:ImplFile:vcbackdrop.cpp
# End Section
# Section Ecs : {FD30FB02-789C-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcFill
# 	2:10:HeaderFile:vcfill1.h
# 	2:8:ImplFile:vcfill1.cpp
# End Section
# Section Ecs : {CD9EFA60-AA40-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcLightSource
# 	2:10:HeaderFile:vclightsource.h
# 	2:8:ImplFile:vclightsource.cpp
# End Section
# Section Ecs : {3080E742-813F-11CE-BECC-00AA0042CB33}
# 	2:5:Class:CVcMarker
# 	2:10:HeaderFile:vcmarker1.h
# 	2:8:ImplFile:vcmarker1.cpp
# End Section
# Section Ecs : {51DCC622-95B7-11CE-86B3-444553540000}
# 	2:5:Class:CVcSeriesPosition
# 	2:10:HeaderFile:vcseriesposition.h
# 	2:8:ImplFile:vcseriesposition.cpp
# End Section
# Section Ecs : {EBF97E20-731F-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcCoor
# 	2:10:HeaderFile:vccoor.h
# 	2:8:ImplFile:vccoor.cpp
# End Section
# Section Ecs : {6FE35CC0-CE50-11CE-8410-00AA0042CB33}
# 	2:5:Class:CVcLightSources
# 	2:10:HeaderFile:vclightsources.h
# 	2:8:ImplFile:vclightsources.cpp
# End Section
# Section Ecs : {C20E5260-B06F-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcDataPoints
# 	2:10:HeaderFile:vcdatapoints1.h
# 	2:8:ImplFile:vcdatapoints1.cpp
# End Section
# Section Ecs : {2F6DD6A0-95E5-11CE-86B3-444553540000}
# 	2:5:Class:CVcStatLine
# 	2:10:HeaderFile:vcstatline.h
# 	2:8:ImplFile:vcstatline.cpp
# End Section
# Section Ecs : {508D02E6-90FC-11CE-86B3-444553540000}
# 	2:5:Class:CVcWeighting
# 	2:10:HeaderFile:vcweighting.h
# 	2:8:ImplFile:vcweighting.cpp
# End Section
# Section Ecs : {027D7900-A023-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcAxis
# 	2:10:HeaderFile:vcaxis1.h
# 	2:8:ImplFile:vcaxis1.cpp
# End Section
# Section Ecs : {FE5517C0-73FE-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcRect
# 	2:10:HeaderFile:vcrect1.h
# 	2:8:ImplFile:vcrect1.cpp
# End Section
# Section Ecs : {6237536C-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcValueScale
# 	2:10:HeaderFile:vcvaluescale1.h
# 	2:8:ImplFile:vcvaluescale1.cpp
# End Section
# Section Ecs : {62375370-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcLabel
# 	2:10:HeaderFile:vclabel1.h
# 	2:8:ImplFile:vclabel1.cpp
# End Section
# Section Ecs : {62375360-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcCategoryScale
# 	2:10:HeaderFile:vccategoryscale1.h
# 	2:8:ImplFile:vccategoryscale1.cpp
# End Section
# Section Ecs : {B54A6420-A25E-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcLight
# 	2:10:HeaderFile:vclight1.h
# 	2:8:ImplFile:vclight1.cpp
# End Section
# Section Ecs : {2F6DD6A4-95E5-11CE-86B3-444553540000}
# 	2:5:Class:CVcDataPoint
# 	2:10:HeaderFile:vcdatapoint1.h
# 	2:8:ImplFile:vcdatapoint1.cpp
# End Section
# Section Ecs : {C14E8B60-AE2B-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcSeriesCollection
# 	2:10:HeaderFile:vcseriescollection1.h
# 	2:8:ImplFile:vcseriescollection1.cpp
# End Section
# Section Ecs : {2E6A37A0-77FC-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcFont
# 	2:10:HeaderFile:vcfont1.h
# 	2:8:ImplFile:vcfont1.cpp
# End Section
# Section Ecs : {62375364-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcAxisGrid
# 	2:10:HeaderFile:vcaxisgrid1.h
# 	2:8:ImplFile:vcaxisgrid1.cpp
# End Section
# Section Ecs : {62B9A400-B93D-11CE-8410-00AA0042CB33}
# 	2:5:Class:CVcLabels
# 	2:10:HeaderFile:vclabels1.h
# 	2:8:ImplFile:vclabels1.cpp
# End Section
# Section Ecs : {508D02E0-90FC-11CE-86B3-444553540000}
# 	2:5:Class:CVcPlotBase
# 	2:10:HeaderFile:vcplotbase1.h
# 	2:8:ImplFile:vcplotbase1.cpp
# End Section
# Section Ecs : {E26C7700-756C-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcTextLayout
# 	2:10:HeaderFile:vctextlayout.h
# 	2:8:ImplFile:vctextlayout.cpp
# End Section
# Section Ecs : {AFE57022-7409-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcShadow
# 	2:10:HeaderFile:vcshadow1.h
# 	2:8:ImplFile:vcshadow1.cpp
# End Section
# Section Ecs : {F75BA680-9057-115E-85B3-448553548000}
# 	2:5:Class:CVcPlot
# 	2:10:HeaderFile:vcplot1.h
# 	2:8:ImplFile:vcplot1.cpp
# End Section
# Section Ecs : {279B5A40-8098-11CE-BECC-00AA0042CB33}
# 	2:5:Class:CVcPen
# 	2:10:HeaderFile:vcpen.h
# 	2:8:ImplFile:vcpen.cpp
# End Section
# Section Ecs : {C82141A0-7571-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcTitle
# 	2:10:HeaderFile:vctitle1.h
# 	2:8:ImplFile:vctitle1.cpp
# End Section
# Section Ecs : {31291E80-728C-11CF-93D5-0020AF99504A}
# 	2:21:DefaultSinkHeaderFile:mschart1.h
# 	2:16:DefaultSinkClass:CMSChart
# End Section
# Section Ecs : {2E6A37A4-77FC-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcFrame
# 	2:10:HeaderFile:vcframe.h
# 	2:8:ImplFile:vcframe.cpp
# End Section
# Section Ecs : {62375368-A17D-11CE-840F-00AA0042CB33}
# 	2:5:Class:CVcTick
# 	2:10:HeaderFile:vctick.h
# 	2:8:ImplFile:vctick.cpp
# End Section
