#include <stdio.h>
#include <
//构建邻居列表的函数
//real为int 或者double
//这个背景是测定原子的邻居,其中N是总的原子数
//MN是每个原子的最多邻居数
//判断两个原子是否为邻居的截断距离平方cutoff_square
//整型数组NN,NN[n]是第n个粒子的邻居个数
//整型数组NL,数组长度为N*MN,NL[n*MN+k]是第n个粒子的第k个邻居的坐标
//x y分别记录每个原子的坐标
void find_neighbor(int *NN,int *NL,const real *x,const real *y){
    for(int n=0;n<N;n++){
        NN[n]=0;
    }
    for(int n1=0;n1<N;++n1){
        real x1=x[n1];
        real y1=y[n1];
        for(int n2=n1+1;n2<N;++n2){
            real x12=x[n2]-x1;
            real y12=y[n2]-y1;
            real distance_square=x12*x12+y12*y12;
            if(distance_square<cutoff_square){
                NL[n1*MN+NN[n1]++]=n2;
                NL[n2*MN+NN[n2]++]=n1;
            }
        }
    }
}

//利用原子操作的cuda版本
void __global__ find_neighbor_atomic (int *d_NL,const real *d_x,const real *d_y,
const int N,const real cutoff_square){
    int n1=blockIdx.x*blockDim.x+threadIdx.x;
    if(n1<N){
        d_NN[n1]=0;
        real x1=d_x[n1];
        real y1=d_y[n1];
        for(int n2=n1+1;n2<N;++n2){
            real x12=d_x[n2]-x1;
            real y12=d_y[n2]-y1;
            real distance_square=x12*x12+y12*y12;
            if(distance_square<cutoff_square){
                d_NL[n1*MN+atomicAdd(&d_NN[n1],1)]=n2;
                d_NL[n2*MN+atomicAdd(&d_NN[n2],1)]=n1;
            }
        }
    }
}