#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <stdexcept>

const int MAX_THREADS = 1000;

template <typename T>
class threadPool {
public:
    explicit threadPool(int number = 1);
    ~threadPool();

    // 不允许拷贝
    threadPool(const threadPool&) = delete;
    threadPool& operator=(const threadPool&) = delete;

    // 添加任务（传入 unique_ptr，转移所有权）
    bool append(std::unique_ptr<T> request);
    // 便捷重载：直接传原始指针（会被封装为 unique_ptr）
    bool append(T* request) { return append(std::unique_ptr<T>(request)); }

    // 只读接口：队列长度（调试/展示用）
    size_t queue_size();

private:
    // 工作线程主循环
    void run();

private:
    std::vector<std::thread> work_threads;//工作线程池,保存所有线程对象
    std::queue<std::unique_ptr<T>> tasks_queue;//任务队列,每一个任务是一个 unique_ptr<T>

    std::mutex queue_mutex;//互斥锁,保证多线程访问安全
    std::condition_variable condition;//条件变量用于线程阻塞/唤醒
    bool stop; // 受 mutex 保护,线程池是否关闭标志
};

// ---------- 实现 ----------
template <typename T>
threadPool<T>::threadPool(int number) : stop(false) {
    if (number <= 0 || number > MAX_THREADS) {
        throw std::invalid_argument("threadPool: invalid thread count");
    }
    for (int i = 0; i < number; ++i) {
        // 每个线程运行成员函数 run()
        work_threads.emplace_back(&threadPool::run, this);
    }
}

template <typename T>
threadPool<T>::~threadPool() {
    {
        // 先把 stop 标志设为 true（在锁内）
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    // 唤醒所有线程，让它们退出
    condition.notify_all();

    // 等待所有线程退出（join）
    for (auto &th : work_threads) {
        if (th.joinable()) th.join();
    }
}

template <typename T>
bool threadPool<T>::append(std::unique_ptr<T> request) {
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        if (stop) return false; // 池已经停止，不接受新任务
        tasks_queue.emplace(std::move(request));
    }
    // 在锁外通知一个等待线程
    condition.notify_one();
    return true;
}

template <typename T>
size_t threadPool<T>::queue_size() {
    std::lock_guard<std::mutex> lock(queue_mutex);
    return tasks_queue.size();
}

template <typename T>
void threadPool<T>::run() {
    while (true) {
        std::unique_ptr<T> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            // 等待：要么 stop 为 true，要么队列非空
            condition.wait(lock, [this]() { return stop || !tasks_queue.empty(); });
            // 如果线程池被停止且没有任务，干净退出
            if (stop && tasks_queue.empty()) return;

            // 取出队首任务（移动出来，避免拷贝）
            task = std::move(tasks_queue.front());
            tasks_queue.pop();
        } // 在这里释放锁 —— 任务在锁外执行

        // 执行任务（捕获异常，避免线程退出）
        if (task) {
            try {
                task->process();
            } catch (...) {
                // 真实工程可记录日志；这里吞掉异常以保持线程存活
            }
        }
    }
}

#endif // THREADPOOL_H
