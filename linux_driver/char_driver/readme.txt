1.执行make
2.insmod chardriverdemo.ko
3.mknode /dev/chardriverdemo c 211 0
gcc -o test test.c
./test
cat /dev/chardriverdemo
