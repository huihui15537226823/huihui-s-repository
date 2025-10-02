#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>

std::atomic<int> counter(0);
std::mutex my_mutex;


void worker()
{
    for (int i = 0; i < 100; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        int old_value = counter.load();
        int new_value;
        do {
            new_value = (old_value == 20) ? 0 : old_value + 1;
        } while (!counter.compare_exchange_strong(old_value, new_value));

        std::lock_guard<std::mutex> lock(my_mutex);
        std::cout << old_value << "\t" << std::this_thread::get_id() << std::endl;
    }
}


void demo()
{
    std::thread t1(worker);
    std::thread t2(worker);

    t1.join();
    t2.join();
}


int main()
{
    demo();
    return 0;
}