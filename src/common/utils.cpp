#include "common/utils.h"

#include <math.h>
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

double get_time(struct timespec *start, struct timespec *end) {
    return (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1e9;
}

void thread_bind(int cpu) {
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    CPU_SET(cpu, &cpu_set);
    if (pthread_setaffinity_np(pthread_self(),
                               sizeof(cpu_set_t), &cpu_set) != 0) {
        fprintf(stderr, "Error: cpu[%d] bind failed.\n", cpu);
        exit(0);
    }
}

void *page_alloc(size_t size) {
    void *data = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    if (data == (void *)-1) {
        fprintf(stderr, "Error(MemData::Construction): mmap failed.\n");
        exit(0);
    }
    return data;
}

void page_free(void *mem, size_t size) {
    munmap(mem, size);
}
