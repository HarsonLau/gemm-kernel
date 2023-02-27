#include <stdlib.h>

#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "common/utils.h"
#include "kernel/m4n24.h"

int main(int argc, char** argv) {
    // args : cpuid K looptime
    // parse arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s cpuid K looptime\n", argv[0]);
        exit(0);
    }
    int cpuid = atoi(argv[1]);
    int K = atoi(argv[2]);
    int looptime = atoi(argv[3]);
    const int M = 4;
    const int N = 24;

    thread_bind(cpuid);
    float* a = (float*)page_alloc(M * K * sizeof(float));
    float* b = (float*)page_alloc(K * N * sizeof(float));
    float* c = (float*)page_alloc(M * N * sizeof(float));
    float* ref = (float*)page_alloc(M * N * sizeof(float));

    srand(time(NULL));
    for (int i = 0; i < M * K; i++) {
        a[i] = (float)rand() / (float)RAND_MAX;
    }

    for (int i = 0; i < K * N; i++) {
        b[i] = (float)rand() / (float)RAND_MAX;
    }
    memset(c, 0, M * N * sizeof(float));
    memset(ref, 0, M * N * sizeof(float));

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < K; k++) {
                ref[i * N + j] += a[i * K + k] * b[k * N + j];
            }
        }
    }

    gemm_m4n24_kernel(a, b, c, M, K, N);

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (fabs(ref[i * N + j] - c[i * N + j]) / fabs(ref[i * N + j]) > 1e-6) {
                fprintf(stderr, "check failed C[%d][%d]: %f ,ref: %f\n", i, j, c[i * N + j], ref[i * N + j]);
                exit(0);
            }
        }
    }

    printf("check passed\n");

    for (int i = 0; i < looptime; i++) {
        gemm_m4n24_kernel(a, b, c, M, K, N);
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int i = 0; i < looptime; i++) {
        gemm_m4n24_kernel(a, b, c, M, K, N);
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double time = get_time(&start, &end);
    double flop = M * N * K * 2.0 * looptime;
    double gflops = flop / time * 1e-9;
    printf("time : %lf s, performance : %lf GFLOPS\n", time, gflops);

    page_free(a, M * K * sizeof(float));
    page_free(b, K * N * sizeof(float));
    page_free(c, M * N * sizeof(float));
    page_free(ref, M * N * sizeof(float));
    return 0;
}