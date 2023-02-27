#ifndef __KERNEL_M24N4_H__
#define __KERNEL_M24N4_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

    void gemm_m4n24_kernel(const float* A, const float* B, float* C, int M, int K, int N);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif
