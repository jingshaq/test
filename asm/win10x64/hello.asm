
; hello.asm
; nasm -f win64 -o hello.obj hello.asm
; "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin\amd64\cl.exe" hello.obj /link "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib\amd64\libcmt.lib" "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10586.0\um\x64\kernel32.Lib" "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\lib\amd64\libvcruntime.lib"  "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10150.0\ucrt\x64\libucrt.lib"  "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.10586.0\um\x64\Uuid.Lib"

global main
extern puts

section .text
main:
        sub rsp, 20h
        mov rcx, message
        call puts
        add rsp, 20h
        ret
message:
        db "Hello",0
