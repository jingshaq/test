# Microsoft Developer Studio Generated NMAKE File, Based on VKeyFdo.dsp
!IF "$(CFG)" == ""
CFG=VKeyFdo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to VKeyFdo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "VKeyFdo - Win32 Release" && "$(CFG)" != "VKeyFdo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VKeyFdo.mak" CFG="VKeyFdo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VKeyFdo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VKeyFdo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VKeyFdo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\VKeyFdo.sys" "$(OUTDIR)\VKeyFdo.bsc"

!ELSE 

ALL : "Test - Win32 Release" "SendKey - Win32 Release" "Setup - Win32 Release" "..\bin\VKeyFdo.sys" "$(OUTDIR)\VKeyFdo.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Setup - Win32 ReleaseCLEAN" "SendKey - Win32 ReleaseCLEAN" "Test - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Dispatch.obj"
	-@erase "$(INTDIR)\Dispatch.sbr"
	-@erase "$(INTDIR)\Init.obj"
	-@erase "$(INTDIR)\Init.sbr"
	-@erase "$(INTDIR)\Pnp.obj"
	-@erase "$(INTDIR)\Pnp.sbr"
	-@erase "$(INTDIR)\Wdmvk.res"
	-@erase "$(OUTDIR)\VKeyFdo.bsc"
	-@erase "$(OUTDIR)\VKeyFdo.pdb"
	-@erase "..\bin\VKeyFdo.sys"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Gz /ML /W3 /WX /Oy /Gy /I "$(ddkroot)\inc\ddk" /I "$(ddkroot)\inc" /D WIN32=100 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DEVL=1 /D FPO=1 /D "_IDWBUILD" /D "NDEBUG" /D _DLL=1 /D _X86_=1 /D i386=1 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Oxs /Zel -cbstring /QIfdiv- /QIf /GF /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wdmvk.res" /i "$(ddkroot)\inc" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VKeyFdo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Dispatch.sbr" \
	"$(INTDIR)\Init.sbr" \
	"$(INTDIR)\Pnp.sbr"

"$(OUTDIR)\VKeyFdo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=int64.lib ntoskrnl.lib hal.lib hidclass.lib /nologo /base:"0x10000" /version:4.0 /entry:"DriverEntry" /incremental:no /pdb:"$(OUTDIR)\VKeyFdo.pdb" /debug /debugtype:coff /machine:IX86 /nodefaultlib /out:"..\bin\VKeyFdo.sys" /libpath:"$(ddkroot)\libfre\i386" /libpath:"$(ddkroot)\lib\i386\free" /driver /debug:notmapped,MINIMAL /IGNORE:4001,4037,4039,4065,4070,4078,4087,4089,4096 /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text /FULLBUILD /RELEASE /FORCE:MULTIPLE /OPT:REF /OPTIDATA /align:0x20 /osversion:4.00 /subsystem:native 
LINK32_OBJS= \
	"$(INTDIR)\Dispatch.obj" \
	"$(INTDIR)\Init.obj" \
	"$(INTDIR)\Pnp.obj" \
	"$(INTDIR)\Wdmvk.res" \
	"..\SendKey\Release\SendKey.lib"

"..\bin\VKeyFdo.sys" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "VKeyFdo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\bin\VKeyFdo.sys" "$(OUTDIR)\VKeyFdo.bsc"

!ELSE 

ALL : "Test - Win32 Debug" "SendKey - Win32 Debug" "Setup - Win32 Debug" "..\bin\VKeyFdo.sys" "$(OUTDIR)\VKeyFdo.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"Setup - Win32 DebugCLEAN" "SendKey - Win32 DebugCLEAN" "Test - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\Dispatch.obj"
	-@erase "$(INTDIR)\Dispatch.sbr"
	-@erase "$(INTDIR)\Init.obj"
	-@erase "$(INTDIR)\Init.sbr"
	-@erase "$(INTDIR)\Pnp.obj"
	-@erase "$(INTDIR)\Pnp.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Wdmvk.res"
	-@erase "$(OUTDIR)\VKeyFdo.bsc"
	-@erase "$(OUTDIR)\VKeyFdo.pdb"
	-@erase "..\bin\VKeyFdo.sys"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /Gz /MLd /W3 /Z7 /Oi /Gy /I "$(ddkroot)\inc\ddk" /I "$(ddkroot)\inc" /D WIN32=100 /D "STD_CALL" /D CONDITION_HANDLING=1 /D NT_UP=1 /D NT_INST=0 /D _NT1X_=100 /D WINNT=1 /D _WIN32_WINNT=0x0400 /D WIN32_LEAN_AND_MEAN=1 /D DBG=1 /D DEVL=1 /D FPO=0 /D "_DEBUG" /D _DLL=1 /D _X86_=1 /D i386=1 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\VKeyFdo.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /Zel -cbstring /QIfdiv- /QIf /GF /c 
MTL_PROJ=/nologo /mktyplib203 /o "NUL" /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\Wdmvk.res" /i "$(ddkroot)\inc" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\VKeyFdo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\Dispatch.sbr" \
	"$(INTDIR)\Init.sbr" \
	"$(INTDIR)\Pnp.sbr"

"$(OUTDIR)\VKeyFdo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=int64.lib ntoskrnl.lib hal.lib hidclass.lib /nologo /base:"0x10000" /version:4.0 /entry:"DriverEntry" /incremental:no /pdb:"$(OUTDIR)\VKeyFdo.pdb" /debug /debugtype:both /machine:IX86 /nodefaultlib /out:"..\bin\VKeyFdo.sys" /libpath:"$(ddkroot)\libchk\i386" /libpath:"$(ddkroot)\lib\i386\checked" /driver /debug:notmapped,FULL /IGNORE:4001,4037,4039,4065,4078,4087,4089,4096 /MERGE:_PAGE=PAGE /MERGE:_TEXT=.text /SECTION:INIT,d /MERGE:.rdata=.text /FULLBUILD /RELEASE /FORCE:MULTIPLE /OPT:REF /OPTIDATA /align:0x20 /osversion:4.00 /subsystem:native 
LINK32_OBJS= \
	"$(INTDIR)\Dispatch.obj" \
	"$(INTDIR)\Init.obj" \
	"$(INTDIR)\Pnp.obj" \
	"$(INTDIR)\Wdmvk.res" \
	"..\SendKey\Debug\SendKey.lib"

"..\bin\VKeyFdo.sys" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("VKeyFdo.dep")
!INCLUDE "VKeyFdo.dep"
!ELSE 
!MESSAGE Warning: cannot find "VKeyFdo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "VKeyFdo - Win32 Release" || "$(CFG)" == "VKeyFdo - Win32 Debug"
SOURCE=.\Dispatch.cpp

"$(INTDIR)\Dispatch.obj"	"$(INTDIR)\Dispatch.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Init.cpp

"$(INTDIR)\Init.obj"	"$(INTDIR)\Init.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Pnp.cpp

"$(INTDIR)\Pnp.obj"	"$(INTDIR)\Pnp.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\Wdmvk.rc

"$(INTDIR)\Wdmvk.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "VKeyFdo - Win32 Release"

"Setup - Win32 Release" : 
   cd "\projects\Fakey\Setup"
   $(MAKE) /$(MAKEFLAGS) /F .\Setup.mak CFG="Setup - Win32 Release" 
   cd "..\VKeyFdo"

"Setup - Win32 ReleaseCLEAN" : 
   cd "\projects\Fakey\Setup"
   $(MAKE) /$(MAKEFLAGS) /F .\Setup.mak CFG="Setup - Win32 Release" RECURSE=1 CLEAN 
   cd "..\VKeyFdo"

!ELSEIF  "$(CFG)" == "VKeyFdo - Win32 Debug"

"Setup - Win32 Debug" : 
   cd "\projects\Fakey\Setup"
   $(MAKE) /$(MAKEFLAGS) /F .\Setup.mak CFG="Setup - Win32 Debug" 
   cd "..\VKeyFdo"

"Setup - Win32 DebugCLEAN" : 
   cd "\projects\Fakey\Setup"
   $(MAKE) /$(MAKEFLAGS) /F .\Setup.mak CFG="Setup - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\VKeyFdo"

!ENDIF 

!IF  "$(CFG)" == "VKeyFdo - Win32 Release"

"SendKey - Win32 Release" : 
   cd "\projects\Fakey\SendKey"
   $(MAKE) /$(MAKEFLAGS) /F .\SendKey.mak CFG="SendKey - Win32 Release" 
   cd "..\VKeyFdo"

"SendKey - Win32 ReleaseCLEAN" : 
   cd "\projects\Fakey\SendKey"
   $(MAKE) /$(MAKEFLAGS) /F .\SendKey.mak CFG="SendKey - Win32 Release" RECURSE=1 CLEAN 
   cd "..\VKeyFdo"

!ELSEIF  "$(CFG)" == "VKeyFdo - Win32 Debug"

"SendKey - Win32 Debug" : 
   cd "\projects\Fakey\SendKey"
   $(MAKE) /$(MAKEFLAGS) /F .\SendKey.mak CFG="SendKey - Win32 Debug" 
   cd "..\VKeyFdo"

"SendKey - Win32 DebugCLEAN" : 
   cd "\projects\Fakey\SendKey"
   $(MAKE) /$(MAKEFLAGS) /F .\SendKey.mak CFG="SendKey - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\VKeyFdo"

!ENDIF 

!IF  "$(CFG)" == "VKeyFdo - Win32 Release"

"Test - Win32 Release" : 
   cd "\projects\Fakey\Test"
   $(MAKE) /$(MAKEFLAGS) /F .\Test.mak CFG="Test - Win32 Release" 
   cd "..\VKeyFdo"

"Test - Win32 ReleaseCLEAN" : 
   cd "\projects\Fakey\Test"
   $(MAKE) /$(MAKEFLAGS) /F .\Test.mak CFG="Test - Win32 Release" RECURSE=1 CLEAN 
   cd "..\VKeyFdo"

!ELSEIF  "$(CFG)" == "VKeyFdo - Win32 Debug"

"Test - Win32 Debug" : 
   cd "\projects\Fakey\Test"
   $(MAKE) /$(MAKEFLAGS) /F .\Test.mak CFG="Test - Win32 Debug" 
   cd "..\VKeyFdo"

"Test - Win32 DebugCLEAN" : 
   cd "\projects\Fakey\Test"
   $(MAKE) /$(MAKEFLAGS) /F .\Test.mak CFG="Test - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\VKeyFdo"

!ENDIF 


!ENDIF 

