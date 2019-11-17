#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <queue>
#include <algorithm>

//1 2 3 4 5 7 9 14 28

enum
{
    TYPE_A = 1,
    TYPE_B = 2,
    TYPE_C = 3,
    TYPE_D = 4,
    TYPE_E = 5,
    TYPE_F = 7,
    TYPE_G = 9,
    TYPE_H = 14,
    TYPE_I = 28,
};

enum
{
    BIN_TYPE_A,
    BIN_TYPE_B,
    BIN_TYPE_C,
    BIN_TYPE_D,
    BIN_TYPE_E,
    BIN_TYPE_F,
    BIN_TYPE_G,
    BIN_TYPE_H,
    BIN_TYPE_I,
};

std::string ToBin(uint);
int Type( int );
int GetType( uint );
int TypeContain( int );
int TypeExtraBits( int );
int eTypeToeBin_Type( int );
int eBin_TypeToeType( int );
bool CanAdd( uint , int);


class CInvertedIndexElement
{
public:
    CInvertedIndexElement();
    ~CInvertedIndexElement();

    void Print();
    void Insert( uint );
    void EncodeAll();
    std::vector< uint > Get();
private:
    void Encode();
    std::vector<uint> Decode();

    std::vector<uint> _encoded;
    std::queue<uint> _tmpValues;
    uint _type, _lastValue;
};

class CInvertedIndex
{
public:
    void Print();
    void Insert(const std::string&, uint);
    void EncodeAll();
    std::vector< uint > Get( const std::string& );

private:
    std::unordered_map<std::string, CInvertedIndexElement> _indexes;
};

#endif