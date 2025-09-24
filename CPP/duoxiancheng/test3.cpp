#include <mutex>
#include <thread>
#include <iostream>
struct Box{
    explicit Box(int num):numthing{num}{}
    int numthing;
    std::mutex m;
};

void transfer(Box &from,Box &to,int num){
    std::unique_lock<std::mutex> lock1(from.m,std::defer_lock);
    std::unique_lock<std::mutex> lock2(from.m,std::defer_lock);
    
    std::lock(lock1, lock2);
    from.numthing-=num;
    to.numthing+=num;
}

int main()
{
    Box acc1(100);
    Box acc2(50);

    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

    t1.join();
    t2.join();
    std::cout << "acc1 num_things: " << acc1.numthing << std::endl;
    std::cout << "acc2 num_things: " << acc2.numthing << std::endl;
}
