#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include "BaseInvertedIndex.h"
#include "SaveQueue.h"
#include "DynamicBitSet.h"
#include "Worker.h"
#include "SaveCounter.h"

#include <array>
#include <thread>
#include <chrono>
#include <tuple>
#include <fstream>
#include <unordered_map>
#include <vector>

class IndexWorker : public Worker{
public:
    enum eCommand{
        add, get
    };

    void Add(const size_t, const uint);
    void Get(const size_t);
    std::vector <std::pair<size_t, DynamicBitSet>>&& FinalGet();
    void Write(std::ofstream&);
    void Read(std::ifstream&);
    inline size_t Size() { return baseii.Size(); }
    inline size_t GetCount() { return getCount; }

private:
    void Main();
    bool CaseWorking() const;

    BaseInvertedIndex baseii;
    SaveQueue <std::tuple<size_t, uint, eCommand>> commands;
    std::vector <std::pair<size_t, DynamicBitSet>> answers;
    SaveCounter getCount;
};

class InvertedIndex{
public:
    InvertedIndex();
    ~InvertedIndex();

    void Insert (const std::string&, const uint);
    void RunGet (const std::string&);
    void Write (const std::string& fileName);
    void Read (const std::string& fileName);
    std::unordered_map <std::string, DynamicBitSet> GetAll();
    size_t Size();

private:
    static const int WORKERS_COUNT = 8;

    void RunWorkers();
    void StopWorkers();

    bool isWorkersRun;
    std::unordered_map <size_t, std::string> getting_strings;
    std::hash <std::string> string_hash;
    std::array<IndexWorker, WORKERS_COUNT> workers;
};

#endif // !INVERTED_INDEX_H
