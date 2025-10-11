#include <stdio.h>

/*
 * Initialize array values on the host.
 */
// 在主机端初始化数组：将数组元素设置为其索引值
void init(int *a, int N)
{
  int i;
  for (i = 0; i < N; ++i)
  {
    a[i] = i;  // 每个元素的值等于其索引
  }
}

__global__ void doubleElements(int *a, int N)
{
  int i;
  // 计算全局线程索引
  i = blockIdx.x * blockDim.x + threadIdx.x;
  // 确保不越界
  if (i < N)
  {
    a[i] *= 2;  // 将元素值翻倍
  }
}

bool checkElementsAreDoubled(int *a, int N)
{
  int i;
  for (i = 0; i < N; ++i)
  {
    // 检查每个元素是否等于其索引值的两倍
    if (a[i] != i*2) return false;
  }
  return true;
}

int main(){
    int N=100;
    int *a;
    size_t size=N * sizeof(int);
    //分配统一内存,使cpu gpu 都能访问
    cudaMallocManaged(&a,size);

    init(a,N);

    // 设置CUDA核函数的执行配置
    size_t threads_per_block = 10;  // 每个块10个线程
    size_t number_of_blocks = 10;  // 总共10个块

    // 启动核函数，并行处理数组
    doubleElements<<<number_of_blocks, threads_per_block>>>(a, N);
    // 等待GPU操作完成
    cudaDeviceSynchronize();

    // 验证结果
    bool areDoubled = checkElementsAreDoubled(a, N);
    printf("All elements were doubled? %s\n", areDoubled ? "TRUE" : "FALSE");

    // 释放统一内存
    cudaFree(a);
}