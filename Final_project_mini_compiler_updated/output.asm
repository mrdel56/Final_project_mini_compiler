section .text
    global main

main:
    push rbp
    mov rbp, rsp
    sub rsp, 136

    mov eax, 77
    mov DWORD PTR [rbp-8], eax
    mov eax, 33
    mov DWORD PTR [rbp-16], eax
    mov eax, 121
    mov DWORD PTR [rbp-112], eax
    mov eax, DWORD PTR [rbp-112]
    mov DWORD PTR [rbp-24], eax
    mov eax, 60
    mov DWORD PTR [rbp-32], eax
    mov eax, 40
    mov DWORD PTR [rbp-40], eax
    mov eax, 2402
    mov DWORD PTR [rbp-120], eax
    mov eax, DWORD PTR [rbp-120]
    mov DWORD PTR [rbp-48], eax
    mov eax, 0
    mov DWORD PTR [rbp-24], eax
    mov eax, 110
    mov DWORD PTR [rbp-96], eax
    mov eax, DWORD PTR [rbp-96]
    mov DWORD PTR [rbp-8], eax
L2:
    mov eax, 9
    mov DWORD PTR [rbp-64], eax

    mov rsp, rbp
    pop rbp
    mov eax, 0
    ret
