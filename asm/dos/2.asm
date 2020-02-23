assume cs:codesg
codesg segment
        mov ax, 0ffffH
        mov ds, ax
        add bx, 6
        mov al, [bx]
		mov ah, 0
		mov dx, 0
		
		mov cx, 3
s:		add dx, ax
		loop s

		mov ax, 4c00h
        int 21H
codesg ends
end