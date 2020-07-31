rem This is a "update qingcloud desktop agent" program.
rem mshta vbscript:createobject("shell.application").shellexecute("%~s0","goto :runas","","runas",1)(window.close)&goto :uacfalse
rem :runas
rem echo UAC Success
C:
cd %~dp0
echo Update GuestAgent service
C:\Windows\System32\cmd.exe /c sc stop "QingCloud Guest Agent"
ping 127.0.0.1 -n 3
del "C:\Program Files\qingcloud-guest-tools\GuestAgent\bak_GuestAgent.exe"
rename "C:\Program Files\qingcloud-guest-tools\GuestAgent\GuestAgent.exe" "C:\Program Files\qingcloud-guest-tools\GuestAgent\bak_GuestAgent.exe"
ping 127.0.0.1 -n 1
copy GuestAgent\GuestAgent.exe "C:\Program Files\qingcloud-guest-tools\GuestAgent" /y
ping 127.0.0.1 -n 1
rem C:\Windows\System32\cmd.exe /c sc start "QingCloud Guest Agent"
shutdown /r /t 1

rem :uacfalse
rem echo UAC Failed