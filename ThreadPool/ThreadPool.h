//
// Created by VivianSnow on 2018/8/1.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include "SafeQueue.h"
#include <thread>
#include <vector>
#include <condition_variable>

class ThreadPool{
public:
    using Task = std::function<void()>;

public:
    ThreadPool(int threadNum = 10) : threadNum(threadNum) {

    }

    void init(){
        for (int i = 0; i < threadNum; i++) {
            threads.push_back(std::thread(&ThreadPool::thread_func, this));
        }
    }

    void add_task(Task task){
        queue.enqueue(task);
    }

    void stop(){
        shutdown = true;

        for(int i = 0; i < threadNum; i++){
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }

    }

private:
     void thread_func() {
        Task func;
        while (!shutdown) {
            if (!queue.empty()) {
                if (queue.dequeue(func))
                    func();
            }
        }
    }


private:
    int threadNum;
    SafeQueue<Task> queue;
    std::vector<std::thread> threads;
    bool shutdown = false;
};



#endif //THREADPOOL_THREADPOOL_H
