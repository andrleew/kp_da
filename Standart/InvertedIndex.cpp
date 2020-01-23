#include "InvertedIndex.h"

void
IndexWorker::Add(const size_t hash, const uint value){
    commands.Push(std::make_tuple(hash, value, eCommand::add));
}

void
IndexWorker::Get(const size_t hash) {
    getCount += 1;
    commands.Push(std::make_tuple(hash, 0, eCommand::get));
}

std::vector <std::pair<std::size_t, DynamicBitSet>>&&
IndexWorker::FinalGet() {
    while (getCount != 0) std::this_thread::sleep_for(std::chrono::microseconds(20));
    return std::move(answers);
}

bool IndexWorker::CaseWorking() const {
    return !commands.Empty();
}

void
IndexWorker::Main(){
    if (commands.Empty()){
        std::this_thread::sleep_for(std::chrono::microseconds(30));
    } else {
        auto p = commands.FrontAndPop();
        switch (std::get<2> (p))
        {
        case eCommand::add:
            baseii.Insert(std::get<0>(p), std::get<1>(p));
            break;
        case eCommand::get:
            getCount -= 1;
            answers.push_back({std::get<0>(p), baseii.Get(std::get<0> (p))});
            break;
        }
    }
}

void
IndexWorker::Write(std::ofstream& ofs){
    baseii.Write(ofs);
}

void
IndexWorker::Read(std::ifstream& ifs) {
    baseii.Read(ifs);
}

InvertedIndex::InvertedIndex ()
    :isWorkersRun (false) {
        RunWorkers();
}

InvertedIndex::~InvertedIndex() {
    StopWorkers();
}

void
InvertedIndex::RunWorkers() {
    if (isWorkersRun) return;
    else isWorkersRun = true;
    for (auto& worker : workers) worker.Run();
}

void
InvertedIndex::StopWorkers() {
    if (!isWorkersRun) return;
    else isWorkersRun = false;
    for (auto& worker : workers) worker.Stop();
}

void
InvertedIndex::Insert (const std::string& str, uint value){
    size_t h = string_hash(str);
    workers[h % WORKERS_COUNT].Add(h, value);
}

void
InvertedIndex::RunGet (const std::string& str) {
    size_t h = string_hash(str);
    if (getting_strings.insert( {h, str} ).second){
        workers[h & WORKERS_COUNT].Get(h);
    }
}

std::unordered_map<std::string, DynamicBitSet>
InvertedIndex::GetAll() {
    std::unordered_map <std::string, DynamicBitSet> m;
    for (auto& worker : workers) {
        for (auto& p : worker.FinalGet()) {
            m.insert({getting_strings.find(p.first)->second, p.second});
        }
    }
    return m;
}

void
InvertedIndex::Write(const std::string& fileName){
    StopWorkers();
    std::ofstream ofs;
    for (uint8_t i = 0; i < WORKERS_COUNT; ++i) {
        ofs.open(fileName + "." + std::to_string(i));
        workers[i].Write(ofs);
        ofs.close();
    }
}

void
InvertedIndex::Read(const std::string& fileName){
    StopWorkers();
    std::ifstream ifs;
    for (uint8_t i = 0; i < WORKERS_COUNT; ++i){
        ifs.open(fileName + "." + std::to_string(i));
        workers[i].Read(ifs);
        ifs.close();
    }
}

size_t
InvertedIndex::Size() {
    size_t count = 0;
    for (auto& worker : workers) count += worker.Size();
    return count;
}