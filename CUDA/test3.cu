#include <stdio.h>

/*
 * Initialize array values on the host.
 */
// �������˳�ʼ�����飺������Ԫ������Ϊ������ֵ
void init(int *a, int N)
{
  int i;
  for (i = 0; i < N; ++i)
  {
    a[i] = i;  // ÿ��Ԫ�ص�ֵ����������
  }
}

__global__ void doubleElements(int *a, int N)
{
  int i;
  // ����ȫ���߳�����
  i = blockIdx.x * blockDim.x + threadIdx.x;
  // ȷ����Խ��
  if (i < N)
  {
    a[i] *= 2;  // ��Ԫ��ֵ����
  }
}

bool checkElementsAreDoubled(int *a, int N)
{
  int i;
  for (i = 0; i < N; ++i)
  {
    // ���ÿ��Ԫ���Ƿ����������ֵ������
    if (a[i] != i*2) return false;
  }
  return true;
}

int main(){
    int N=100;
    int *a;
    size_t size=N * sizeof(int);
    //����ͳһ�ڴ�,ʹcpu gpu ���ܷ���
    cudaMallocManaged(&a,size);

    init(a,N);

    // ����CUDA�˺�����ִ������
    size_t threads_per_block = 10;  // ÿ����10���߳�
    size_t number_of_blocks = 10;  // �ܹ�10����

    // �����˺��������д�������
    doubleElements<<<number_of_blocks, threads_per_block>>>(a, N);
    // �ȴ�GPU�������
    cudaDeviceSynchronize();

    // ��֤���
    bool areDoubled = checkElementsAreDoubled(a, N);
    printf("All elements were doubled? %s\n", areDoubled ? "TRUE" : "FALSE");

    // �ͷ�ͳһ�ڴ�
    cudaFree(a);
}