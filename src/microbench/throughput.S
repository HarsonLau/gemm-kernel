.globl throughput_test
.type throughput_test, @function
throughput_test:
    movq %rdi, %rax
.loop:
    vfmadd231ps %ymm0, %ymm0, %ymm0
    vfmadd231ps %ymm1, %ymm1, %ymm1
    vfmadd231ps %ymm2, %ymm2, %ymm2
    vfmadd231ps %ymm3, %ymm3, %ymm3
    vfmadd231ps %ymm4, %ymm4, %ymm4
    vfmadd231ps %ymm5, %ymm5, %ymm5
    vfmadd231ps %ymm6, %ymm6, %ymm6
    vfmadd231ps %ymm7, %ymm7, %ymm7
    vfmadd231ps %ymm8, %ymm8, %ymm8
    vfmadd231ps %ymm9, %ymm9, %ymm9
    sub $1, %rax
    jnz .loop
    ret
    