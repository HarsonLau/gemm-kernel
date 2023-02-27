#include "microbench/latency.h"

#include <stdlib.h>

#include <cstdio>

#include "common/utils.h"

int main(int argc, char **argv) {
    // arguments : cpuid looptime (double)freq
    // parse arguments
    if (argc != 4) {
        fprintf(stderr, "Usage: %s cpuid looptime (double)freq\n", argv[0]);
        exit(0);
    }
    int cpuid = atoi(argv[1]);
    double looptime = atof(argv[2]);
    double freq = atof(argv[3]);

    thread_bind(cpuid);

    // warm up
    latency_test(looptime);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    latency_test((long long)looptime);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    double time = get_time(&start, &end);
    printf("loop time : %lf \n", looptime);
    printf("time: %lf s\n", time);

    printf("latency: %lf cycles\n", time * freq / (looptime * 10.0));

    return 0;
}
