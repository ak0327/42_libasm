section .text
    global ft_strlen            ; グローバルに公開

ft_strlen:
    push    rbp                 ; ベースポインタrbpをスタックに退避
    xor     rax, rax            ; raxレジスタを0に初期化

.loop:
    cmp     BYTE [rdi + rax], 0 ; s[i] と '\0' を比較
    je      .end                ; s[i] == '\0' であればendにjmp
    inc     rax                 ; i++
    jmp     .loop

.end:
    pop     rbp                 ; ベースポインタを復元
    ret
