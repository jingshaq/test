@echo off
%1 %2
mshta vbscript:createobject("shell.application").shellexecute("%~s0","goto :runas","","runas",1)(window.close)&goto :uacfalse
:runas
echo UAC Success
pause
goto :eof

:uacfalse
echo UAC Failed
pause