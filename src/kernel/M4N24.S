/* param rdi:      mat a */
/* param rsi:      mat b */
/* param rdx:      mat c */
/* param ecx:      M     */
/* param r8d:      K     */
/* param r9d:      N     */

/*C: ymm0 ymm1  ymm2  */
/*   ymm3 ymm4  ymm5  */
/*   ymm6 ymm7  ymm8  */
/*   ymm9 ymm10 ymm11 */

/*B: ymm12 ymm13 ymm14*/

.globl gemm_m4n24_kernel
.type gemm_m4n24_kernel, @function
gemm_m4n24_kernel:
    pushq %rbx
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15

    # &A[0][0]
    movq %rdi, %r12                 # &A[0][0]
    leaq (%rdi,%r8,4), %r13        # &A[1][0] = &A[0][0] + K * sizeof(float)
    leaq (%rdi,%r8,8), %r14        # &A[2][0] = &A[0][0] + 2 * K * sizeof(float)  
    leaq (%r14,%r8,4), %r15       # &A[3][0] = &A[0][0] + 3 * K * sizeof(float)

    # load C to ymm0-ymm11
    vmovaps   0(%rdx), %ymm0
    vmovaps  32(%rdx), %ymm1
    vmovaps  64(%rdx), %ymm2
    vmovaps  96(%rdx), %ymm3
    vmovaps 128(%rdx), %ymm4
    vmovaps 160(%rdx), %ymm5
    vmovaps 192(%rdx), %ymm6
    vmovaps 224(%rdx), %ymm7
    vmovaps 256(%rdx), %ymm8
    vmovaps 288(%rdx), %ymm9
    vmovaps 320(%rdx), %ymm10
    vmovaps 352(%rdx), %ymm11

    xorq %rax, %rax                 # k = 0
.loop:
    # load B[k][0] B[k][8] B[k][16] to ymm12-ymm14
    vmovaps 0(%rsi), %ymm12
    vmovaps 32(%rsi), %ymm13
    vmovaps 64(%rsi), %ymm14
    add $96, %rsi                   # B += N * sizeof(float)

    
    vbroadcastss (%r12,%rax,4), %ymm15      # load A[0][k] to ymm15
    vfmadd231ps %ymm15, %ymm12, %ymm0
    vfmadd231ps %ymm15, %ymm13, %ymm1
    vfmadd231ps %ymm15, %ymm14, %ymm2

    vbroadcastss (%r13,%rax,4), %ymm15     # load A[1][k] to ymm15
    vfmadd231ps %ymm15, %ymm12, %ymm3
    vfmadd231ps %ymm15, %ymm13, %ymm4
    vfmadd231ps %ymm15, %ymm14, %ymm5

    vbroadcastss (%r14,%rax,4), %ymm15     # load A[2][k] to ymm15
    vfmadd231ps %ymm15, %ymm12, %ymm6
    vfmadd231ps %ymm15, %ymm13, %ymm7
    vfmadd231ps %ymm15, %ymm14, %ymm8

    vbroadcastss (%r15,%rax,4), %ymm15     # load A[3][k] to ymm15
    vfmadd231ps %ymm15, %ymm12, %ymm9
    vfmadd231ps %ymm15, %ymm13, %ymm10
    vfmadd231ps %ymm15, %ymm14, %ymm11

    add $1, %rax
    cmp %r8d, %eax
    jne .loop

    # store C to memory
    vmovaps %ymm0, 0(%rdx)
    vmovaps %ymm1, 32(%rdx)
    vmovaps %ymm2, 64(%rdx)
    vmovaps %ymm3, 96(%rdx)
    vmovaps %ymm4, 128(%rdx)
    vmovaps %ymm5, 160(%rdx)
    vmovaps %ymm6, 192(%rdx)
    vmovaps %ymm7, 224(%rdx)
    vmovaps %ymm8, 256(%rdx)
    vmovaps %ymm9, 288(%rdx)
    vmovaps %ymm10, 320(%rdx)
    vmovaps %ymm11, 352(%rdx)

    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rbx
    ret

    

    