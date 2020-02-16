### 说明
1.编辑汇编源码: hello.asm 或 hello.s
2.编译汇编源码: nasm -f macho64 hello.asm 或 nasm -f macho64 -o hello.o hello.asm
3.链接形成可执行文件: ld hello.o -o hello -macosx_version_min 10.13 -lSystem
4.执行可执行文件: ./hello
