org 0x7c00
BaseOfStack equ 0x7c00

Label_Start:

    ; set segment register. Useless. All of them can be set 0x0
    mov ax, cs
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, BaseOfStack

    ; clear screen. int 10h/AH=06h. AL=0 means clear the sceen, then BX, CX, DX can be anythig.
    mov ax, 0600h
    mov bx, 0700h
    mov cx, 0
    mov dx, 184fh
    int 10h

    ; set focus
    mov ax, 0200h
    mov bx, 0000h
    mov dx, 0000h
    int 10h

;=======	display on screen. int 10h/AH=13h. ES:BP=>String Address, CX: String size, 

	mov	ax,	1301h
	mov	bx,	000fh
	mov	dx,	0000h
	mov	cx,	10
	push	ax
	mov	ax,	ds
	mov	es,	ax
	pop	ax
	mov	bp,	StartBootMessage
	int	10h

;=======	reset floppy

	xor	ah,	ah
	xor	dl,	dl
	int	13h

	jmp	$

StartBootMessage:	db	"Start Boot"

;=======	fill zero until whole sector

	times	510 - ($ - $$)	db	0
	dw	0xaa55
