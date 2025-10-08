#include <stdio.h>

int main(){
    int deviceId;
    cudaGetDevice(&deviceId);

    // 创建设备属性结构体并获取设备属性
    cudaDeviceProp props;
    cudaGetDeviceProperties(&props, deviceId);

    // 基本设备信息
    int computeCapabilityMajor = props.major;
    int computeCapabilityMinor = props.minor;
    int multiProcessorCount = props.multiProcessorCount;
    int warpSize = props.warpSize;
    int maxThreadsPerBlock = props.maxThreadsPerBlock;
    int maxThreadsPerMultiProcessor = props.maxThreadsPerMultiProcessor;

    // 计算Warp相关信息
    int warpsPerSM = maxThreadsPerMultiProcessor / warpSize;
    int totalWarps = warpsPerSM * multiProcessorCount;

    // 获取维度限制
    int maxThreadsDim[3] = {props.maxThreadsDim[0],
                                props.maxThreadsDim[1],
                                props.maxThreadsDim[2]};

    int maxGridSize[3] = {props.maxGridSize[0],
                               props.maxGridSize[1],
                               props.maxGridSize[2]};

    // 获取内存信息
    size_t totalGlobalMem = props.totalGlobalMem;
    size_t sharedMemPerBlock = props.sharedMemPerBlock;

    // 打印完整设备信息
    printf("\n===== CUDA 设备属性 =====\n");
    printf("\n基本信息:\n");
    printf("设备名称: %s\n", props.name);
    printf("设备ID: %d\n", deviceId);
    printf("计算能力: %d.%d\n", computeCapabilityMajor, computeCapabilityMinor);

    printf("\n处理器信息:\n");
    printf("SM数量: %d\n", multiProcessorCount);
    printf("每个SM的最大线程数: %d\n", maxThreadsPerMultiProcessor);
    printf("每个块的最大线程数: %d\n", maxThreadsPerBlock);

    printf("\nWarp信息:\n");
    printf("Warp大小: %d\n", warpSize);
    printf("每个SM的Warp数量: %d\n", warpsPerSM);
    printf("总Warp数量: %d\n", totalWarps);

    printf("\n维度限制:\n");
    printf("最大线程维度: (%d, %d, %d)\n",
           maxThreadsDim[0], maxThreadsDim[1], maxThreadsDim[2]);
    printf("最大网格维度: (%d, %d, %d)\n",
           maxGridSize[0], maxGridSize[1], maxGridSize[2]);

    printf("\n内存信息:\n");
    printf("全局内存: %.2f GB\n", (float)totalGlobalMem / (1024*1024*1024));
    printf("每块共享内存: %zu KB\n", sharedMemPerBlock / 1024);

    printf("\n理论性能:\n");
    printf("最大并发线程数: %d\n", multiProcessorCount * maxThreadsPerMultiProcessor);
    printf("最大并发Warp数: %d\n", totalWarps);

    return 0;
}