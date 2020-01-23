#include "Worker.h"

Worker::Worker()
    :isRunning (false) {}
Worker::~Worker() {
    Stop();
}

void Worker::Run(){
    if (isRunning) return;
    isRunning = true;
    workerThread = std::thread(&Worker::SubMain, this);
}

void Worker::Stop(){
    if (!isRunning) return;
    isRunning = false;
    workerThread.join();
}

void Worker::SubMain(){
    while (isRunning || CaseWorking()) Main();
}

bool Worker::CaseWorking() const {
    return false;
}

void Worker::Main(){
}