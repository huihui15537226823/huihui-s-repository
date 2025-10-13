#pragma once
#include <stdio.h>
#include <cuda_runtime.h>

#define CHECK(call)                                                   \
do {                                                                  \
    const cudaError_t error_code = (call);                            \
    if (error_code != cudaSuccess) {                                  \
        fprintf(stderr, "CUDA ERROR:\n");                             \
        fprintf(stderr, "  File:        %s\n", __FILE__);             \
        fprintf(stderr, "  Line:        %d\n", __LINE__);             \
        fprintf(stderr, "  Error code:  %d\n", error_code);           \
        fprintf(stderr, "  Error text:  %s\n",                        \
                cudaGetErrorString(error_code));                      \
        exit(EXIT_FAILURE);                                           \
    }                                                                 \
} while (0)
