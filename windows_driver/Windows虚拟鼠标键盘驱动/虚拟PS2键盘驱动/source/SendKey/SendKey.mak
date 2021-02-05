# Microsoft Developer Studio Generated NMAKE File, Based on SendKey.dsp
!IF "$(CFG)" == ""
CFG=SendKey - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SendKey - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SendKey - Win32 Release" && "$(CFG)" != "SendKey - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SendKey.mak" CFG="SendKey - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SendKey - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SendKey - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "SendKey - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "..\bin\SendKey.dll" "$(OUTDIR)\SendKey.bsc"


CLEAN :
	-@erase "$(INTDIR)\SendKey.obj"
	-@erase "$(INTDIR)\SendKey.pch"
	-@erase "$(INTDIR)\sendkey.res"
	-@erase "$(INTDIR)\SendKey.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SendKey.bsc"
	-@erase "$(OUTDIR)\SendKey.exp"
	-@erase "$(OUTDIR)\SendKey.lib"
	-@erase "..\bin\SendKey.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SENDKEY_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SendKey.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\sendkey.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SendKey.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\SendKey.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\SendKey.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\SendKey.pdb" /machine:I386 /out:"../bin/SendKey.dll" /implib:"$(OUTDIR)\SendKey.lib" 
LINK32_OBJS= \
	"$(INTDIR)\SendKey.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\sendkey.res"

"..\bin\SendKey.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SendKey - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug

ALL : "..\bin\SendKey.dll"


CLEAN :
	-@erase "$(INTDIR)\SendKey.obj"
	-@erase "$(INTDIR)\SendKey.pch"
	-@erase "$(INTDIR)\sendkey.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SendKey.exp"
	-@erase "$(OUTDIR)\SendKey.lib"
	-@erase "$(OUTDIR)\SendKey.pdb"
	-@erase "..\bin\SendKey.dll"
	-@erase "..\bin\SendKey.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SENDKEY_EXPORTS" /Fp"$(INTDIR)\SendKey.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\sendkey.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SendKey.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\SendKey.pdb" /debug /machine:I386 /out:"../bin/SendKey.dll" /implib:"$(OUTDIR)\SendKey.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SendKey.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\sendkey.res"

"..\bin\SendKey.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("SendKey.dep")
!INCLUDE "SendKey.dep"
!ELSE 
!MESSAGE Warning: cannot find "SendKey.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SendKey - Win32 Release" || "$(CFG)" == "SendKey - Win32 Debug"
SOURCE=.\SendKey.cpp

!IF  "$(CFG)" == "SendKey - Win32 Release"


"$(INTDIR)\SendKey.obj"	"$(INTDIR)\SendKey.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SendKey.pch"


!ELSEIF  "$(CFG)" == "SendKey - Win32 Debug"


"$(INTDIR)\SendKey.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SendKey.pch"


!ENDIF 

SOURCE=.\sendkey.rc

"$(INTDIR)\sendkey.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SendKey - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SENDKEY_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SendKey.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SendKey.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SendKey - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SENDKEY_EXPORTS" /Fp"$(INTDIR)\SendKey.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SendKey.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

