#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int cargo = 0;
bool ready_to_consume = false; // 标记：是否有货物可以消费

// 消费者
void consume(int n) {
    for (int i = 0; i < n; ++i) {
        std::unique_lock<std::mutex> lck(mtx);
        // 没有货物时等待
        cv.wait(lck, [] { return ready_to_consume; });
        std::cout << "Consume: " << cargo << '\n';
        cargo = 0;
        ready_to_consume = false;
        cv.notify_one(); // 通知生产者可以继续生产
    }
}

// 生产者
int main() {
    std::thread consumer_thread(consume, 10);

    for (int i = 0; i < 10; ++i) {
        std::unique_lock<std::mutex> lck(mtx);
        // 如果上一次的货物还没消费，就等待
        cv.wait(lck, [] { return !ready_to_consume; });
        cargo = i + 1;
        std::cout << "Produce: " << cargo << '\n';
        ready_to_consume = true;
        cv.notify_one(); // 通知消费者可以消费
    }

    consumer_thread.join();
    return 0;
}