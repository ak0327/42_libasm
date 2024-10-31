; ft_write.s
%ifdef __APPLE__
    extern ___error
%else
    extern __errno_location
%endif

global ft_read
default rel
section .text

; fd: rdi
; buf: rsi
; nbyte: rdx
ft_read:
    mov  rax, 0         ; read
    syscall             ; call read

    cmp rax, 0
    jge .success        ; 0以上なら成功
    jmp .failure

.success:
    ret

.failure:
    mov rdi, rax        ; エラーコードを一時保存
    neg rdi             ; 正の値に変換
%ifdef __APPLE__
    call ___error wrt ..plt
%else
    call __errno_location wrt ..plt
%endif
    mov [rax], rdi      ; errnoを書き換え
    mov rax, -1         ; -1を返却
    ret
