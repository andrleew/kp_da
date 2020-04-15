#ifndef SAVE_COUNTER_H
#define SAVE_COUNTER_H

#include <mutex>

class SaveCounter{
public:
    SaveCounter(const size_t _count = 0)
    : count (_count) {}

    template <typename T>
    SaveCounter& operator += (const T& t) {
        const std::lock_guard<std::mutex> lock (cmtx);
        count += static_cast<size_t> (t);
        return *this;
    }

    template <typename T>
    SaveCounter& operator -=(const T& t) {
        const std::lock_guard<std::mutex> lock (cmtx);
        count -= static_cast<size_t> (t);
        return *this;
    }

    operator size_t(){
        return count;
    }

private:
    size_t count;
    std::mutex cmtx;
};


#endif