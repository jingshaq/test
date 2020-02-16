### 说明
1.编辑汇编源码: hello.asm
2.编译汇编源码:  nasm -f elf64 hello.asm
3.链接形成可执行文件: ld -o hello hello.o 如果把hello.asm代码里面_start改为main，可以用gcc链接： gcc -o hello hello.o 或  gcc -no-pie -o hello hello.o
4.执行可执行文件: ./hello
