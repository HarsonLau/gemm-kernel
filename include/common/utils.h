#ifndef __GEMM_KERNEL_UTILS_H__
#define __GEMM_KERNEL_UTILS_H__

#include <time.h>

double get_time(struct timespec *start, struct timespec *end);

void thread_bind(int cpu);

void *page_alloc(size_t size);

void page_free(void *mem, size_t size);

#endif // __GEMM_KERNEL_UTILS_H__
