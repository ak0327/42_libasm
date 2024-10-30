global ft_strcmp
section .text

ft_strcmp:
.loop:
    mov     al, byte [rdi]        ; al <- *s1
    mov     bl, byte [rsi]        ; bl <- *s2
    cmp     al, bl
    jne     .return_diff

    test    al, al
    je      .return_zero

    inc     rdi                   ; *(s1)++
    inc     rsi                   ; *(s2)++
    jmp     .loop

.return_diff:
    movsx   eax, al               ; alを8->32bitに符号拡張してeaxに格納
    movsx   ebx, bl               ; blを8->32bitに符号拡張してebxに格納
    sub     eax, ebx              ; eax = eax - ebx
    ret

.return_zero:
    xor     eax, eax
    ret
