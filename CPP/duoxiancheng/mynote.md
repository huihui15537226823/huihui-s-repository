**join 和detach区别**,join后面的代码不会被执行除非子线程结束,而detach启动的线程在后台运行,当前代码继续执行不等待新线程结束

​可以使用joinable判断是join模式还是detach模式。

```text
if (myThread.joinable()) foo.join();
```

**this_thread**,四个功能函数为get_id(获取线程id)，yield(放弃线程执行，回到就绪状态)，sleep_for(暂停一秒)，sleep_until(一分钟之后执行吗，如下)
例子：
using std::chrono::system_clock;
std::time_t tt = system_clock::to_time_t(system_clock::now());
struct std::tm * ptm = std::localtime(&tt);
cout << "Waiting for the next minute to begin...\n";
++ptm->tm_min; //加一分钟
ptm->tm_sec = 0; //秒数设置为0//暂停执行，到下一整分执行
this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));

**mutex**
常用操作：
lock，unlock
trylock{1 未上锁返回false，并锁住；2 其他线程已经上锁，返回true；3 同一个线程已经对他上锁，将会产生死锁}

lock_guard
创建lock_guard对象时，它将尝试获取提供给它的互斥锁的所有权。当控制流离开lock_guard对象的作用域时，lock_guard析构并释放互斥量。lock_guard的特点：
创建即加锁，作用域结束自动析构并解锁，无需手工解锁
不能中途解锁，必须等作用域结束才解锁
不能复制

