; ft_strdup.s
global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy
default rel
section .text

; s  : rdi
; ret: rax
ft_strdup:
    push rdi            ;
    call ft_strlen      ; rax = ft_strlen(rdi)

    inc rax             ; rax++, 終端ヌル文字用
    mov rdi, rax
    call malloc wrt ..plt ; rax = malloc(rdi)

    test rax, rax
    jz .error

    mov rdi, rax        ; dst = rax
    pop rsi             ; src = rsi = rdi(stack)
    call ft_strcpy      ; ft_strcpy(dst, src)

    ret

.error:
    pop rdi             ; スタックを戻す
    ret
