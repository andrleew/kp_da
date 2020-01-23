#ifndef WORKER_H
#define WORKER_H

#include <thread>

class Worker {
public:
    Worker();
    virtual ~Worker();

    void Run();
    void Stop();


private:
    void SubMain();
    virtual void Main();
    virtual bool CaseWorking() const;

    bool isRunning;
    std::thread workerThread;
};

#endif // !WORKER_H