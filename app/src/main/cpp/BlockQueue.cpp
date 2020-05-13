//
// Created by sqwu on 2020/5/13.
//

#include "BlockQueue.h"
#pragma once
#include <condition_variable>
#include <mutex>
#include <deque>
#include<iostream>
#include <stdio.h>
#include <thread>
#include "log.h"

template<class T>
class BlockQueue
{
public:
    typedef std::unique_lock<std::mutex> TLock;

    //maxCapacity为-1，代表队列无最大限制
    explicit BlockQueue(const int maxCapacity = -1):m_maxCapacity(maxCapacity)
    {

    }

    size_t size()
    {

        TLock lock(m_mutex);
        int size1 = m_list.size();
//        lock.unlock();
        return size1;
    }

    void push_back(const T &item)
    {
        TLock lock(m_mutex);
        if (true == hasCapacity())
        {
            while (m_list.size() >= m_maxCapacity)
            {
                LOGE("queue", "数据已经填满，所以阻塞%s", "");
                m_notFull.wait(lock);
//                m_notEmpty.notify_all();
            }
        }

        m_list.push_back(item);
        LOGE("queue", "生产数据：%d,添加之后长度：%d", item, m_list.size());
        m_notEmpty.notify_all();
        lock.unlock();
    }

    T pop()
    {
        TLock lock(m_mutex);
        while (m_list.empty())
        {
            LOGE("queue", "没有数据所以阻塞%s", "");
            m_notEmpty.wait(lock);
        }

        T temp = *m_list.begin();
        m_list.pop_front();

        m_notFull.notify_all();
        LOGE("queue", "消费数据：%d， 消费之后剩余长度：%d", temp, m_list.size());
        lock.unlock();
        return temp;
    }

    bool empty()
    {
        TLock lock(m_mutex);
        return m_list.empty();
    }

    bool full()
    {
        if ( false == hasCapacity())
        {
            return false;
        }

        TLock lock(m_mutex);
        return m_list.size() >= m_maxCapacity;
    }

private:
    bool hasCapacity() const
    {
        return m_maxCapacity > 0;
    }

    typedef std::deque<T> TList;
    TList m_list;

    const int m_maxCapacity;

    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
};



typedef BlockQueue<int> TQueue;

void produce(TQueue &queue)
{
    const int num = 1000;
    for (int i = 0; i < num; ++i)
    {
        queue.push_back(i);
        LOGE("queue", "--------------------------------------生产数据：%d", i);
//        LOGE("queue", "生产数据：%d,添加之后长度：%d", i, queue.size());
    }
}

void consume(TQueue &queue)
{
    while (true)
    {
        int tmp = queue.pop();
        printf("%d\n", tmp);
        LOGE("queue", "---------------------------------------消费数据：%d", tmp);
        std::this_thread::get_id();
//        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int test() {
    TQueue queue(20);
    std::thread t1(produce, std::ref(queue));
    std::thread t2(consume, std::ref(queue));
    std::thread t3(consume, std::ref(queue));
    t3.join();
    t2.join();
    t1.join();
    return 0;

}
