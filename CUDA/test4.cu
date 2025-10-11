#include <stdio.h>
//CUDA处理宏,包装cuda函数调用
#define gpuErrchk(ans) {gpuAssert((ans),__FILE__, __LINE__);}

//错误处理辅助函数
inline void gpuAssert(cudaError_t code,const char *file,int line){
    if(code!=cudaSuccess){
        fprintf(stderr,"GPU错误:%s\n 文件:%s\n 行号:%d\n", cudaGetErrorString(code),file,line);
        exit(code);
    }
}

// CPU函数：用指定值初始化数组
void initWith(float num, float *a, int N)
{
  for(int i = 0; i < N; ++i)
  {
    a[i] = num;
  }
}

// GPU核函数：并行执行向量加法
// 使用网格跨度循环处理大数组
__global__ void addVectorsInto(float *result,float *a,float *b,int N){
    // 计算当前线程的全局索引
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    // 计算网格总大小（总线程数）
    int stride = blockDim.x * gridDim.x;

    
}