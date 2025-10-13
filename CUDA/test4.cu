#include <stdio.h>
//CUDA�����,��װcuda��������
#define gpuErrchk(ans) {gpuAssert((ans),__FILE__, __LINE__);}

//������������
inline void gpuAssert(cudaError_t code,const char *file,int line){
    if(code!=cudaSuccess){
        fprintf(stderr,"GPU����:%s\n �ļ�:%s\n �к�:%d\n", cudaGetErrorString(code),file,line);
        exit(code);
    }
}

// CPU��������ָ��ֵ��ʼ������
void initWith(float num, float *a, int N)
{
  for(int i = 0; i < N; ++i)
  {
    a[i] = num;
  }
}

// GPU�˺���������ִ�������ӷ�
// ʹ��������ѭ�����������
__global__ void addVectorsInto(float *result,float *a,float *b,int N){
    // ���㵱ǰ�̵߳�ȫ������
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    // ���������ܴ�С�����߳�����
    int stride = blockDim.x * gridDim.x;

    // ʹ��������ѭ����ÿ���̴߳�����Ԫ��
    for(int i = index; i < N; i += stride){
        result[i] = a[i] + b[i];
    }
}

// CPU��������֤����Ƿ���ȷ
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
  // ���������С��2^21 = 2,097,152��Ԫ��
  const int N = 2<<20;
  size_t size = N * sizeof(float);

  // ������������������ָ��
  float *a;
  float *b;
  float *c;

  // ����ͳһ�ڴ棬ʹCPU��GPU���ܷ���
  gpuErrchk(cudaMallocManaged(&a, size));
  gpuErrchk(cudaMallocManaged(&b, size));
  gpuErrchk(cudaMallocManaged(&c, size));

  // ��ʼ�����飺aȫΪ3��bȫΪ4��cȫΪ0
  initWith(3, a, N);
  initWith(4, b, N);
  initWith(0, c, N);

  // ����CUDA�˺���ִ������
  int threadsPerBlock = 256;
  // ������Ҫ�Ŀ�����ȷ���ܴ�������Ԫ��
  int numberOfBlocks = (N + threadsPerBlock - 1) / threadsPerBlock;

  // �����˺������������ӷ�
  addVectorsInto<<<numberOfBlocks, threadsPerBlock>>>(c, a, b, N);
  // ���˺�����������
  gpuErrchk(cudaPeekAtLastError());
  // �ȴ�GPU��ɲ��������ʱ����
  gpuErrchk(cudaDeviceSynchronize());

  // ��֤���������Ԫ��Ӧ�õ���7��3+4��
  checkElementsAre(7, c, N);

  // �ͷ�ͳһ�ڴ�
  gpuErrchk(cudaFree(a));
  gpuErrchk(cudaFree(b));
  gpuErrchk(cudaFree(c));

  return 0;
}