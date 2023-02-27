.globl latency_test
.type latency_test, @function
latency_test:
    // prama looptime: %rdi
    vxorps %ymm1, %ymm1, %ymm1
    vxorps %ymm2, %ymm2, %ymm2
    vxorps %ymm3, %ymm3, %ymm3
    vxorps %ymm4, %ymm4, %ymm4
    vxorps %ymm5, %ymm5, %ymm5
    vxorps %ymm6, %ymm6, %ymm6
    vxorps %ymm7, %ymm7, %ymm7
    vxorps %ymm8, %ymm8, %ymm8
    vxorps %ymm9, %ymm9, %ymm9
    vxorps %ymm10, %ymm10, %ymm10
    vxorps %ymm11, %ymm11, %ymm11
    vxorps %ymm12, %ymm12, %ymm12
    vxorps %ymm13, %ymm13, %ymm13
    vxorps %ymm14, %ymm14, %ymm14
    vxorps %ymm15, %ymm15, %ymm15
.loop:
    vfmadd231ps %ymm0, %ymm0, %ymm1
    vfmadd231ps %ymm1, %ymm1, %ymm2
    vfmadd231ps %ymm2, %ymm2, %ymm3
    vfmadd231ps %ymm3, %ymm3, %ymm4
    vfmadd231ps %ymm4, %ymm4, %ymm5
    vfmadd231ps %ymm5, %ymm5, %ymm6
    vfmadd231ps %ymm6, %ymm6, %ymm7
    vfmadd231ps %ymm7, %ymm7, %ymm8
    vfmadd231ps %ymm8, %ymm8, %ymm9
    vfmadd231ps %ymm9, %ymm9, %ymm0
    sub $0x1, %rdi
    jne .loop

    ret
    