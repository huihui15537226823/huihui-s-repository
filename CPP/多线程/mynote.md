 	**join 和detach区别**,join后面的代码不会被执行除非子线程结束,而detach启动的线程在后台运行,当前代码继续执行不等待新线程结束

​	可以使用joinable判断是join模式还是detach模式。

```text
if (myThread.joinable()) foo.join();
```

**this_thread**