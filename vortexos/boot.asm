[org 0x7c00]
_start:
    cli
    mov ax, 0x00
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7c00
    mov byte [color_actual], 0x0a
reiniciar_pantalla:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    call aplicar_color_fondo
    mov si, texto_bienvenida
mostrar_inicio:
    lodsb
    cmp al, 0
    je iniciar_linea
    mov ah, 0x0e
    mov bh, 0x00
    mov bl, [color_actual]
    int 0x10
    jmp mostrar_inicio
iniciar_linea:
    mov ah, 0x0e
    mov al, '>'
    int 0x10
    mov al, ' '
    int 0x10
    mov word [buffer_index], 0
bucle_teclado:
    mov ah, 0x00
    int 0x16
    cmp al, 0x0d
    je es_enter
    cmp al, 0x08
    je es_backspace
    mov bx, [buffer_index]
    cmp bx, 10
    jge bucle_teclado
    cmp al, 'A'
    jl guardar_letra
    cmp al, 'Z'
    jg guardar_letra
    add al, 32
guardar_letra:
    mov [cmd_buffer + bx], al
    inc word [buffer_index]
    mov ah, 0x0e
    mov bh, 0x00
    mov bl, [color_actual]
    int 0x10
    jmp bucle_teclado
es_backspace:
    mov bx, [buffer_index]
    cmp bx, 0
    je bucle_teclado
    dec word [buffer_index]
    mov ah, 0x0e
    mov al, 0x08
    int 0x10
    mov al, ' '
    int 0x10
    mov al, 0x08
    int 0x10
    jmp bucle_teclado
es_enter:
    mov bx, [buffer_index]
    mov byte [cmd_buffer + bx], 0
    mov ah, 0x0e
    mov al, 0x0a
    int 0x10
    mov al, 0x0d
    int 0x10
    cmp word [buffer_index], 0
    je iniciar_linea

    mov si, cmd_buffer
    mov di, str_clear
    call comparar_strings
    jc reiniciar_pantalla

    mov si, cmd_buffer
    mov di, str_matrix
    call comparar_strings
    jc ejecutar_matrix

    mov si, cmd_buffer
    mov di, str_delay
    call comparar_strings
    jc ejecutar_delay

    mov si, cmd_buffer
    mov di, str_blue
    call comparar_strings
    jc ejecutar_blue

    mov si, cmd_buffer
    mov di, str_dark
    call comparar_strings
    jc ejecutar_dark

    mov si, cmd_buffer
    mov di, str_green
    call comparar_strings
    jc ejecutar_green

    mov si, cmd_buffer
    mov di, str_red
    call comparar_strings
    jc ejecutar_red

    mov si, cmd_buffer
    mov di, str_shutdown
    call comparar_strings
    jc ejecutar_shutdown

    mov ah, 0x0e
    mov al, 'E'
    int 0x10
    mov al, 0x0a
    int 0x10
    mov al, 0x0d
    int 0x10
    jmp iniciar_linea

ejecutar_shutdown:
    mov ax, 0x2000
    mov dx, 0x604
    out dx, ax
    hlt

ejecutar_blue:
    mov byte [color_actual], 0x1f
    jmp reiniciar_pantalla
ejecutar_dark:
    mov byte [color_actual], 0x0f
    jmp reiniciar_pantalla
ejecutar_green:
    mov byte [color_actual], 0x2f
    jmp reiniciar_pantalla
ejecutar_red:
    mov byte [color_actual], 0x4f
    jmp reiniciar_pantalla

ejecutar_delay:
    mov ah, 0x00
    int 0x1a
    mov bx, dx
    add bx, 55
.esperar:
    mov ah, 0x00
    int 0x1a
    cmp dx, bx
    jb .esperar
    jmp iniciar_linea

ejecutar_matrix:
    mov ah, 0x00
    mov al, 0x03
    int 0x10
.bucle_m:
    mov ah, 0x01
    int 0x16
    jnz reiniciar_pantalla
    
    mov ah, 0x00
    int 0x1a
    mov ax, dx
    xor dx, dx
    mov cx, 10
    div cx
    
    mov al, dl
    add al, '0'
    
    mov ah, 0x0e
    mov bh, 0x00
    mov bl, 0x0a
    int 0x10
    
    mov cx, 0x00
    mov dx, 0x2000
    mov ah, 0x86
    int 0x15
    jmp .bucle_m

comparar_strings:
.bucle:
    mov al, [si]
    mov bl, [di]
    cmp al, bl
    jne .diferentes
    cmp al, 0
    je .iguales
    inc si
    inc di
    jmp .bucle
.diferentes:
    clc
    ret
.iguales:
    stc
    ret

aplicar_color_fondo:
    mov ax, 0xb800
    mov es, ax
    mov bx, 1
    mov al, [color_actual]
.bucle_color:
    mov [es:bx], al
    add bx, 2
    cmp bx, 4000
    jl .bucle_color
    ret

texto_bienvenida: db "Vortex3.5", 0x0d, 0x0a, 0
str_clear:    db "clear", 0
str_shutdown: db "shutdown", 0
str_matrix:   db "matrix", 0
str_delay:    db "delay", 0
str_blue:     db "b", 0          ; Comandos de 1 sola letra para ahorrar espacio
str_dark:     db "d", 0
str_green:    db "g", 0
str_red:      db "r", 0

color_actual: db 0
buffer_index: dw 0
cmd_buffer:   times 12 db 0

times 510-($-$$) db 0
dw 0xaa55
