#include <stdio.h>

int main(){
    int deviceId;
    cudaGetDevice(&deviceId);

    // �����豸���Խṹ�岢��ȡ�豸����
    cudaDeviceProp props;
    cudaGetDeviceProperties(&props, deviceId);

    // �����豸��Ϣ
    int computeCapabilityMajor = props.major;
    int computeCapabilityMinor = props.minor;
    int multiProcessorCount = props.multiProcessorCount;
    int warpSize = props.warpSize;
    int maxThreadsPerBlock = props.maxThreadsPerBlock;
    int maxThreadsPerMultiProcessor = props.maxThreadsPerMultiProcessor;

    // ����Warp�����Ϣ
    int warpsPerSM = maxThreadsPerMultiProcessor / warpSize;
    int totalWarps = warpsPerSM * multiProcessorCount;

    // ��ȡά������
    int maxThreadsDim[3] = {props.maxThreadsDim[0],
                                props.maxThreadsDim[1],
                                props.maxThreadsDim[2]};

    int maxGridSize[3] = {props.maxGridSize[0],
                               props.maxGridSize[1],
                               props.maxGridSize[2]};

    // ��ȡ�ڴ���Ϣ
    size_t totalGlobalMem = props.totalGlobalMem;
    size_t sharedMemPerBlock = props.sharedMemPerBlock;

    // ��ӡ�����豸��Ϣ
    printf("\n===== CUDA �豸���� =====\n");
    printf("\n������Ϣ:\n");
    printf("�豸����: %s\n", props.name);
    printf("�豸ID: %d\n", deviceId);
    printf("��������: %d.%d\n", computeCapabilityMajor, computeCapabilityMinor);

    printf("\n��������Ϣ:\n");
    printf("SM����: %d\n", multiProcessorCount);
    printf("ÿ��SM������߳���: %d\n", maxThreadsPerMultiProcessor);
    printf("ÿ���������߳���: %d\n", maxThreadsPerBlock);

    printf("\nWarp��Ϣ:\n");
    printf("Warp��С: %d\n", warpSize);
    printf("ÿ��SM��Warp����: %d\n", warpsPerSM);
    printf("��Warp����: %d\n", totalWarps);

    printf("\nά������:\n");
    printf("����߳�ά��: (%d, %d, %d)\n",
           maxThreadsDim[0], maxThreadsDim[1], maxThreadsDim[2]);
    printf("�������ά��: (%d, %d, %d)\n",
           maxGridSize[0], maxGridSize[1], maxGridSize[2]);

    printf("\n�ڴ���Ϣ:\n");
    printf("ȫ���ڴ�: %.2f GB\n", (float)totalGlobalMem / (1024*1024*1024));
    printf("ÿ�鹲���ڴ�: %zu KB\n", sharedMemPerBlock / 1024);

    printf("\n��������:\n");
    printf("��󲢷��߳���: %d\n", multiProcessorCount * maxThreadsPerMultiProcessor);
    printf("��󲢷�Warp��: %d\n", totalWarps);

    return 0;
}