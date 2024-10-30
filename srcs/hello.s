section .data
    msg db 'Hello, world!', 0xA
    len equ $ - msg

section .text
    global print_hello
    print_hello:
        ; レジスタを保存
        push rbp
        mov rbp, rsp

        ; 相対アドレッシングを使用してmsgのアドレスを計算
        lea rsi, [rel msg]  ; メッセージのアドレスをrsiにロード
        mov rdx, len        ; メッセージの長さをrdxにロード
        mov rdi, 1          ; stdout (ファイルディスクリプタ)
        mov rax, 1          ; writeシステムコール
        syscall             ; システムコールの呼び出し

        ; スタックを戻す
        pop rbp
        ret
