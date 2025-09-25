#include "threadpool.h"
#include <iostream>
#include <cmath>
#include <chrono>

// 用户任务类：必须提供 void process()
class Task {
public:
    Task(int id): id(id) {}
    void process() {
        // 模拟耗时工作
        long n = 200000;
        while (n--) {
            volatile double x = std::sqrt((double)n);
            (void)x;
        }
        std::cout << "Task " << id << " done\n";
    }
private:
    int id;
};

int main() {
    threadPool<Task> pool(4); // 4 个工作线程

    for (int i = 0; i < 10; ++i) {
        pool.append(std::make_unique<Task>(i));
        std::cout << "Queue size: " << pool.queue_size() << '\n';
    }

    // pool 在析构时会等待所有线程退出（join）
    // 给几秒钟让线程完成演示（真实工程不需要）
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
