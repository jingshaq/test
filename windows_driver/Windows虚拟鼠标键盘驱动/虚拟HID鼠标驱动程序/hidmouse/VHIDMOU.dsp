# Microsoft Developer Studio Project File - Name="VHIDMOU" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=VHIDMOU - Win32 Checked
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VHIDMOU.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VHIDMOU.mak" CFG="VHIDMOU - Win32 Checked"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VHIDMOU - Win32 Free" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "VHIDMOU - Win32 Checked" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VHIDMOU - Win32 Free"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Free"
# PROP BASE Intermediate_Dir "Free"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir ".\objfre\i386\"
# PROP Intermediate_Dir ".\objfre\i386\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /Gz /W3 /Oy /Gy /I "$(DRIVERWORKS)\..\common\include\stl" /I "$(TARGET_INC_PATH)" /I "$(CRT_INC_PATH)" /I "$(WDM_INC_PATH)" /I "$(DDK_INC_PATH)" /I "$(BASEDIR)\src\wdm\hid\inc" /I "$(BASEDIR)\src\hid\inc" /I "$(DRIVERWORKS)\Include" /I "$(DRIVERWORKS)\source" /I "$(DRIVERWORKS)\include\dep_vxd" /I "$(DRIVERWORKS)\include\dep_wdm" /I "$(DRIVERWORKS)\include\dep_ndis" /FI"warning.h" /D NTVERSION='WDM' /D _X86_=1 /D i386=1 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D WIN32=100 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D FPO=1 /FR /Zel -cbstring /GF /QIfdiv- /QIf /Oxs /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /i "$(DRIVERWORKS)\include" /d "NDEBUG" /d NTVERSION='WDM'
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 wdm.lib "$(DRIVERWORKS)\lib\i386\free\vdw_wdm.lib" hidclass.lib /nologo /base:"0x10000" /version:5.0 /stack:0x40000,0x1000 /entry:"DriverEntry" /machine:IX86 /nodefaultlib /out:".\objfre\i386\VHIDMOU.sys" /libpath:"$(TARGET_LIB_PATH)" /driver /IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096,4210 /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text /FULLBUILD /RELEASE /OPT:REF /OPT:ICF /align:0x80 /osversion:5.00 /subsystem:native,1.10 /debug:MINIMAL /driver:WDM
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - ---------------------------Build SoftICE Symbols----------------------------
TargetPath=.\objfre\i386\VHIDMOU.sys
TargetName=VHIDMOU
InputPath=.\objfre\i386\VHIDMOU.sys
SOURCE="$(InputPath)"

".\objfre\i386\$(TARGETNAME).nms" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(DRIVERWORKS)\bin\nmsym /trans:source,package,always $(TARGETPATH)

# End Custom Build

!ELSEIF  "$(CFG)" == "VHIDMOU - Win32 Checked"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Checked"
# PROP BASE Intermediate_Dir "Checked"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir ".\objchk\i386\"
# PROP Intermediate_Dir ".\objchk\i386\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD CPP /nologo /Gz /ML /W3 /Zi /Oi /Gy /I "$(DRIVERWORKS)\..\common\include\stl" /I "$(TARGET_INC_PATH)" /I "$(CRT_INC_PATH)" /I "$(WDM_INC_PATH)" /I "$(DDK_INC_PATH)" /I "$(BASEDIR)\src\wdm\hid\inc" /I "$(BASEDIR)\src\hid\inc" /I "$(DRIVERWORKS)\Include" /I "$(DRIVERWORKS)\source" /I "$(DRIVERWORKS)\include\dep_vxd" /I "$(DRIVERWORKS)\include\dep_wdm" /I "$(DRIVERWORKS)\include\dep_ndis" /FI"warning.h" /D NTVERSION='WDM' /D _X86_=1 /D i386=1 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D WIN32=100 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D DBG=1 /D FPO=0 /FR /Fd".\objchk\i386\\VHIDMOU.pdb" /Zel -cbstring /GF /QIfdiv- /QIf /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /i "$(DRIVERWORKS)\include" /d "_DEBUG" /d NTVERSION='WDM'
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /machine:IX86
# ADD LINK32 wdm.lib "$(DRIVERWORKS)\lib\i386\checked\vdw_wdm.lib" hidclass.lib /nologo /base:"0x10000" /version:5.0 /stack:0x40000,0x1000 /entry:"DriverEntry" /incremental:no /machine:IX86 /nodefaultlib /out:".\objchk\i386\VHIDMOU.sys" /libpath:"$(TARGET_LIB_PATH)" /driver /IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096,4210 /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text /FULLBUILD /RELEASE /OPT:REF /OPT:ICF /align:0x80 /osversion:5.00 /subsystem:native,1.10 /debug:FULL /driver:WDM
# SUBTRACT LINK32 /pdb:none
# Begin Custom Build - ---------------------------Build SoftICE Symbols----------------------------
TargetPath=.\objchk\i386\VHIDMOU.sys
TargetName=VHIDMOU
InputPath=.\objchk\i386\VHIDMOU.sys
SOURCE="$(InputPath)"

".\objchk\i386\$(TARGETNAME).nms" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	$(DRIVERWORKS)\bin\nmsym /trans:source,package,always $(TARGETPATH)

# End Custom Build

!ENDIF 

# Begin Target

# Name "VHIDMOU - Win32 Free"
# Name "VHIDMOU - Win32 Checked"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\vhidmou.cpp
DEP_CPP_VHIDM=\
	"..\..\..\..\..\..\..\ntddk\inc\alpharef.h"\
	"..\..\..\..\..\..\..\ntddk\inc\basetsd.h"\
	"..\..\..\..\..\..\..\ntddk\inc\bugcodes.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\afilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\efilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\ffilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\ndis.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\ntddk.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\tfilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\wdm\1394.h"\
	"..\..\..\..\..\..\..\ntddk\inc\guiddef.h"\
	"..\..\..\..\..\..\..\ntddk\inc\hidclass.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ia64reg.h"\
	"..\..\..\..\..\..\..\ntddk\inc\netevent.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntddndis.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntdef.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntiologc.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntstatus.h"\
	"..\..\..\..\..\..\..\ntddk\inc\wdm.h"\
	"..\..\..\..\..\..\..\ntddk\inc\wmistr.h"\
	"..\..\..\..\..\..\..\ntddk\src\wdm\hid\inc\hidport.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\common\include\stcinit.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\cpprt.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\cright.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_ndis\kndiscpp.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_ndis\KNdisList.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_ndis\KNdisSpinLock.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_vxd\vtoolscp.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_vxd\vxdntlib.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\dwcontrl.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394async.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394Irb.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394isoc.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kadapter.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kaddress.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\karray.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kbus.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kchecker.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kcontrol.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdevice.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdevque.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdispobj.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdmaxfer.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdmqex.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdmqueue.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdpc.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdriver.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kerrlog.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kevent.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kfifo.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kfile.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kfilter.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kgenlock.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kheap.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\khid.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kicount.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kimgsect.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kintrupt.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kiocparm.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kirp.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\klist.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\klower.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kmemory.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kmutex.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kndisvdw.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kpcicfg.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kphysdev.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kpnpdev.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kpnplow.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kquery.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kregkey.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kresreq.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ksemaphr.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ksfifo.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kspin.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kstdwmi.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ksysthrd.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ktimer.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ktrace.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kunitnam.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kustring.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kvxdintf.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\Kwdmfltr.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kwmi.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kwmiblock.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kwmistr.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kworkitm.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ShFifo.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\vdw.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\source\khid.cpp"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\source\shfifo.cpp"\
	".\function.h"\
	".\vhidmou.h"\
	".\vmoudev.h"\
	
# End Source File
# Begin Source File

SOURCE=.\vmoudev.cpp
DEP_CPP_VMOUD=\
	"..\..\..\..\..\..\..\ntddk\inc\alpharef.h"\
	"..\..\..\..\..\..\..\ntddk\inc\basetsd.h"\
	"..\..\..\..\..\..\..\ntddk\inc\bugcodes.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\afilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\efilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\ffilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\ndis.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\ntddk.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\tfilter.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ddk\wdm\1394.h"\
	"..\..\..\..\..\..\..\ntddk\inc\guiddef.h"\
	"..\..\..\..\..\..\..\ntddk\inc\hidclass.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ia64reg.h"\
	"..\..\..\..\..\..\..\ntddk\inc\netevent.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntddndis.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntdef.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntiologc.h"\
	"..\..\..\..\..\..\..\ntddk\inc\ntstatus.h"\
	"..\..\..\..\..\..\..\ntddk\inc\wdm.h"\
	"..\..\..\..\..\..\..\ntddk\inc\wmistr.h"\
	"..\..\..\..\..\..\..\ntddk\src\wdm\hid\inc\hidport.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\common\include\stcinit.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\cpprt.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\cright.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_ndis\kndiscpp.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_ndis\KNdisList.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_ndis\KNdisSpinLock.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_vxd\vtoolscp.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\include\dep_vxd\vxdntlib.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\dwcontrl.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394async.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394Irb.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\k1394isoc.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kadapter.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kaddress.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\karray.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kbus.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kchecker.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kcontrol.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdevice.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdevque.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdispobj.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdmaxfer.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdmqex.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdmqueue.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdpc.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kdriver.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kerrlog.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kevent.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kfifo.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kfile.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kfilter.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kgenlock.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kheap.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\khid.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kicount.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kimgsect.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kintrupt.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kiocparm.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kirp.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\klist.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\klower.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kmemory.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kmutex.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kndisvdw.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kpcicfg.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kphysdev.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kpnpdev.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kpnplow.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kquery.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kregkey.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kresreq.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ksemaphr.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ksfifo.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kspin.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kstdwmi.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ksysthrd.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ktimer.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ktrace.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kunitnam.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kustring.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kvxdintf.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\Kwdmfltr.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kwmi.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kwmiblock.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kwmistr.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\kworkitm.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\ShFifo.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\Include\vdw.h"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\source\khid.cpp"\
	"..\..\..\..\..\..\..\PROGRA~1\COMPUW~1\DRIVER~1\DRIVER~3\source\shfifo.cpp"\
	".\function.h"\
	".\hidmouse.h"\
	".\vmoudev.h"\
	
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\function.h
# End Source File
# Begin Source File

SOURCE=.\hidmouse.h
# End Source File
# Begin Source File

SOURCE=.\vhidmou.h
# End Source File
# Begin Source File

SOURCE=.\vmoudev.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\vhidmou.rc
# End Source File
# End Group
# End Target
# End Project
