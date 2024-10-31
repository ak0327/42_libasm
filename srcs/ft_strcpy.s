; ft_strcpy.s
global ft_strcpy
section .text

; ABI P.20 引数の順番: rdi, rsi, rdx, rcx, r8, r9
ft_strcpy:
    push    rdi

.loop:
    mov     al, byte [rsi]  ; al <- *src
    mov     byte [rdi], al  ; *dst <- al
    test    al, al          ; *src == '\0'
    je      .done

    inc     rdi             ; *(dst)++
    inc     rsi             ; *(src)++
    jmp     .loop

.done:
    pop     rax
    ret
