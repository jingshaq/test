# Microsoft Developer Studio Generated NMAKE File, Based on Test.dsp
!IF "$(CFG)" == ""
CFG=Test - Win32 Debug
!MESSAGE No configuration specified. Defaulting to Test - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "Test - Win32 Release" && "$(CFG)" != "Test - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Test.mak" CFG="Test - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Test - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Test - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "Test - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "..\bin\Test.exe" "$(OUTDIR)\Test.bsc"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\Test.obj"
	-@erase "$(INTDIR)\Test.pch"
	-@erase "$(INTDIR)\Test.res"
	-@erase "$(INTDIR)\Test.sbr"
	-@erase "$(INTDIR)\TestDlg.obj"
	-@erase "$(INTDIR)\TestDlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\Test.bsc"
	-@erase "..\bin\Test.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Test.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Test.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\Test.sbr" \
	"$(INTDIR)\TestDlg.sbr"

"$(OUTDIR)\Test.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=../sendkey/release/sendkey.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\Test.pdb" /machine:I386 /out:"../bin/Test.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Test.obj" \
	"$(INTDIR)\TestDlg.obj" \
	"$(INTDIR)\Test.res"

"..\bin\Test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "Test - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\bin\Test.exe"


CLEAN :
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\Test.obj"
	-@erase "$(INTDIR)\Test.pch"
	-@erase "$(INTDIR)\Test.res"
	-@erase "$(INTDIR)\TestDlg.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\Test.pdb"
	-@erase "..\bin\Test.exe"
	-@erase "..\bin\Test.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Test.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\Test.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\Test.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=../sendkey/debug/sendkey.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\Test.pdb" /debug /machine:I386 /out:"../bin/Test.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\Test.obj" \
	"$(INTDIR)\TestDlg.obj" \
	"$(INTDIR)\Test.res"

"..\bin\Test.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("Test.dep")
!INCLUDE "Test.dep"
!ELSE 
!MESSAGE Warning: cannot find "Test.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "Test - Win32 Release" || "$(CFG)" == "Test - Win32 Debug"
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "Test - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\Test.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\Test.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "Test - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\Test.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\Test.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\Test.cpp

!IF  "$(CFG)" == "Test - Win32 Release"


"$(INTDIR)\Test.obj"	"$(INTDIR)\Test.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test.pch"


!ELSEIF  "$(CFG)" == "Test - Win32 Debug"


"$(INTDIR)\Test.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test.pch"


!ENDIF 

SOURCE=.\Test.rc

"$(INTDIR)\Test.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\TestDlg.cpp

!IF  "$(CFG)" == "Test - Win32 Release"


"$(INTDIR)\TestDlg.obj"	"$(INTDIR)\TestDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test.pch"


!ELSEIF  "$(CFG)" == "Test - Win32 Debug"


"$(INTDIR)\TestDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\Test.pch"


!ENDIF 


!ENDIF 

