#include "utils.h"
#include <cstdio>

int main(int argc, char **argv) {
    thread_bind(0);

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    auto ptr = page_alloc(1024);
    clock_gettime(CLOCK_REALTIME, &end);

    printf("Time: %lf\n", get_time(&start, &end));
    page_free(ptr, 1024);
  return 0;
}
