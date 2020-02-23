assume cs:code,ds:data,ss:stack      ; 定义代码段，数据段，栈段
data segment 
    dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
data ends     ; 数据段结束

stack segment
    dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0      ; 16个字
stack ends      ; 栈段结束
    
code segment
start:  mov ax,stack    ; 将CPU分配给栈段的地址赋值给ax寄存器
        mov ss,ax        ; 然后在赋值给ss栈段寄存器
        mov sp,20h        ; 将栈顶指针设置在32的位置
        
        mov ax,data
        mov ds,ax        ; ds指向data段
        mov bx,0        ; 将ds[bx]指向data段的第一个单元
        
        mov cx,8        ; 循环8次
     s :push [bx]        ; 将数据段的第0个值push进栈段
        add bx,2        ; 因为一个字2字节
        loop s            ; 将data段的8个字，依次入栈
        
        mov cx,8
     s0:pop [bx]        ; 此时(bx)=16，将栈中数据pop出放进数据段内存单元=16中
        add bx,2
        loop s0            ; 出栈8个字，依次放进16~31内存单元中
        
        mov ax,4c00H
        int 21H
        
code ends   ; 代码段结束
end start