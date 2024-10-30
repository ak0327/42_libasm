global ft_strlen                ; グローバルに公開
section .text

ft_strlen:
    push    rbp                 ; ベースポインタrbpをスタックに退避
    xor     rax, rax            ; raxレジスタを0に初期化

.loop:
    cmp     byte [rdi + rax], 0 ; s[i] と '\0' を比較
    je      .done               ; s[i] == '\0' であればendにjmp
    inc     rax                 ; i++
    jmp     .loop

.done:
    pop     rbp                 ; ベースポインタを復元
    ret
