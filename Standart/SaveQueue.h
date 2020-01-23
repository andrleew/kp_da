#ifndef SAVE_QUEUE_H
#define SAVE_QUEUE_H

#include <mutex>
#include <queue>

template <class T>
class SaveQueue {
public:
    void Push(const T& t) {
        qmtx.lock();
            q.push(t);
        qmtx.unlock();
    }

    void Pop(const T& t) {
        qmtx.lock();
            q.pop();
        qmtx.unlock();
    }

    T& Front() const {
        return q.front();
    }

    T FrontAndPop() {
        qmtx.lock();
            T t = q.front();
            q.pop();
        qmtx.unlock();
        return t;
    }

    inline
    size_t Size() const{
        return q.size();
    }

    inline
    bool Empty() const{
        return q.empty();
    }

private:
    std::mutex qmtx;
    std::queue <T> q;
    bool isLocked;
};

#endif