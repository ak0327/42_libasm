section .data
    msg db 'Hello, world!', 0xA
    len equ $ - msg

section .text
    global _start

_start:
    ; write(1, msg, len)
    mov rax, 1             ; システムコール番号 1 (sys_write)
    mov rdi, 1             ; ファイルディスクリプタ 1 (stdout)
    mov rsi, msg           ; 出力メッセージのアドレス
    mov rdx, len           ; メッセージの長さ
    syscall                ; システムコール

    ; exit(0)
    mov rax, 60            ; システムコール番号 60 (sys_exit)
    xor rdi, rdi           ; ステータスコード 0
    syscall                ; システムコール
