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

    // 使用网格跨度循环，每个线程处理多个元素
    for(int i = index; i < N; i += stride){
        result[i] = a[i] + b[i];
    }
}

// CPU函数：验证结果是否正确
void checkElementsAre(float target, float *array, int N)
{
  for(int i = 0; i < N; i++)
  {
    if(array[i] != target)
    {
      printf("FAIL: array[%d] - %0.0f does not equal %0.0f\n", i, array[i], target);
      exit(1);
    }
  }
  printf("SUCCESS! All values added correctly.\n");
}

int main(){
  // 设置数组大小：2^21 = 2,097,152个元素
  const int N = 2<<20;
  size_t size = N * sizeof(float);

  // 声明三个浮点数数组指针
  float *a;
  float *b;
  float *c;

  // 分配统一内存，使CPU和GPU都能访问
  gpuErrchk(cudaMallocManaged(&a, size));
  gpuErrchk(cudaMallocManaged(&b, size));
  gpuErrchk(cudaMallocManaged(&c, size));

  // 初始化数组：a全为3，b全为4，c全为0
  initWith(3, a, N);
  initWith(4, b, N);
  initWith(0, c, N);

  // 设置CUDA核函数执行配置
  int threadsPerBlock = 256;
  // 计算需要的块数，确保能处理所有元素
  int numberOfBlocks = (N + threadsPerBlock - 1) / threadsPerBlock;

  // 启动核函数进行向量加法
  addVectorsInto<<<numberOfBlocks, threadsPerBlock>>>(c, a, b, N);
  // 检查核函数启动错误
  gpuErrchk(cudaPeekAtLastError());
  // 等待GPU完成并检查运行时错误
  gpuErrchk(cudaDeviceSynchronize());

  // 验证结果：所有元素应该等于7（3+4）
  checkElementsAre(7, c, N);

  // 释放统一内存
  gpuErrchk(cudaFree(a));
  gpuErrchk(cudaFree(b));
  gpuErrchk(cudaFree(c));

  return 0;
}