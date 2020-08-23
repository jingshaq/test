说明：
    本例中，驱动没有回归缓冲区位置，因此在test.c中在write数据后，调用lseek将文件指针修改到起始位置。
1.执行make
2.insmod chardriverdemo.ko
3.mknode /dev/chardriverdemo c 211 0
gcc -o test test.c
./test
cat /dev/chardriverdemo
