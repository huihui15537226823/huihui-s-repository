//常见生产者-消费者模型

#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable

std::mutex mtx;
std::condition_variable cv;
int cargo = 0;
bool shipment_available() 
{
    return cargo!=0;
}
void consume (int n) 
{
    for (int i=0; i<n; ++i) 
    {
        std::unique_lock<std::mutex> lck(mtx);//自动上锁
        //第二个参数为false才阻塞（wait），阻塞完即unlock，给其它线程资源
        cv.wait(lck,shipment_available);// consume:
        std::cout << cargo << '\n';
        cargo=0;
    }
}
int main ()
{
    std::thread consumer_thread (consume,10);
    for (int i=0; i<10; ++i) 
    {
        //每次cargo每次为0才运行。
        while (shipment_available())  std::this_thread::yield();
        std::unique_lock<std::mutex> lck(mtx);
        cargo = i+1;
        cv.notify_one();
    }

    consumer_thread.join();
    return 0;
}