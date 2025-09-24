#include <iostream>
#include <thread>
using namespace std;

void thread_1()
{
    cout<<"子线程1"<<endl;
}

void thread_2(int x)
{
    cout<<"x:"<<x<<endl;
    cout<<"子线程2"<<endl;
}

int main()
{
  thread first ( thread_1); // 开启线程，调用：thread_1()
  thread second (thread_2,100); // 开启线程，调用：thread_2(100)
  //thread third(thread_2,3);//开启第3个线程，共享thread_2函数。
  std::cout << "主线程\n";

  first.join(); //必须说明添加线程的方式            
  second.join(); 
  std::cout << "子线程结束.\n";//必须join完成
  return 0;
}