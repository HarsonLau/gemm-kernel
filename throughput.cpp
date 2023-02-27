#include "microbench/throughput.h"

#include <stdlib.h>

#include <cstdio>

#include "common/utils.h"

int main(int argc, char **argv) {
    // args: cpuid looptime
    // parse arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s cpuid looptime\n", argv[0]);
        exit(0);
    }

    int cpuid = atoi(argv[1]);
    double looptime = atof(argv[2]);

    thread_bind(cpuid);

    throughput_test((long long)looptime);
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    throughput_test((long long)looptime);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    double time = get_time(&start, &end);
    printf("time: %lf s\n", time);
    double gflops = 2.0 * 8 * 16.0 * looptime / time * 1e-9;
    printf("peak: %lf GFLOPS\n", gflops);

    return 0;
}
