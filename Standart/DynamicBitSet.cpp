#include "DynamicBitSet.h"

// inline int
// DynamicBitSet::_ChunkPow(){
//     return sizeof (uint32_t) + 1;
// }

// inline size_t
// DynamicBitSet::_DivChunk(size_t num)
// { return num >> ( _ChunkPow() ); }

// inline size_t
// DynamicBitSet::_ModChunk(size_t num)
// { return num % ( _ChunkLength() ); }

// inline int
// DynamicBitSet::_ChunkLength()
// { return (1 << _ChunkPow()); }


DynamicBitSet::DynamicBitSet( const DynamicBitSet& dbs):
_size(dbs._size),
_bitLength(dbs._bitLength),
_count(dbs._count){
    _array = static_cast<uint32_t*>( malloc(sizeof(uint32_t) * _size));
    for (decltype(_size)i (0); i < _size; ++i) _array[i] = dbs._array[i];
}


DynamicBitSet::DynamicBitSet( const DynamicBitSet&& dbs):
_size(dbs._size),
_bitLength(dbs._bitLength),
_count(dbs._count){
    _array = static_cast<uint32_t*>( malloc(sizeof(uint32_t) * _size));
    for (decltype(_size)i (0); i < _size; ++i) _array[i] = dbs._array[i];
}

DynamicBitSet::DynamicBitSet(size_t size):
_size(_DivChunk(size) + (_ModChunk(size) != 0)),
_bitLength(size),
_count(0)
{
    _array = static_cast<uint32_t*>(calloc(_size, sizeof(uint32_t)));
}

DynamicBitSet::~DynamicBitSet()
{
    free (_array);
}   

size_t
DynamicBitSet::_BitCount(uint v){
    size_t count = 0;
    while (v){
        count += (v & 1);
        v >>= 1;
    }
    return count;
}

std::vector <uint32_t>
DynamicBitSet::ToVector(){
    // std::cout << _count << std::endl;
    std::vector<uint32_t> res(_count);
    auto data = res.data();
    size_t k = 0;
    for (size_t i = 0; i < _size && k < _count; ++i){
        for (size_t j = 0; j < _ChunkLength() && k < _count; ++j){
            data[k] = i * _ChunkLength() + j;
            k += (_array[i] & (1 << j)) != 0;
        }
    }
    return res;
}

void
DynamicBitSet::Not(size_t maxSize){
    uint32_t size = (_DivChunk(maxSize) + (_ModChunk(maxSize) != 0));
    if (_size < size) _array = static_cast<uint32_t*> (realloc(_array, sizeof(uint32_t) * size));
    decltype(_size) i;
    for (i = 0; i < _size; ++i) _array[i] = ONES32 ^ _array[i];
    for (; i < size; ++i) _array[i] = ONES32;
    _size = std::max(size, _size);
    _count = _bitLength - _count + (size - _size);
    _bitLength = std::max(static_cast<size_t>(_bitLength), maxSize);
}

DynamicBitSet&
DynamicBitSet::operator&=(const DynamicBitSet& rhs){
    _size = std::min(_size, rhs._size);
    _bitLength = std::min(_bitLength, rhs._bitLength);
    _count = 0;
    for (decltype(_size) i = 0; i < _size; ++i){
        _array[i] &= rhs._array[i];
        _count += _BitCount(_array[i]);
    }
    return *this;
}

DynamicBitSet&
DynamicBitSet::operator|=(const DynamicBitSet& rhs){
    if (_size < rhs._size){
        _array = static_cast<uint32_t*>( realloc(_array, sizeof(uint32_t) * rhs._size) );
        for (auto i = _size; i < rhs._size; ++i) _array = 0;
        _size = rhs._size;
    }
    _bitLength = std::max(_bitLength, rhs._bitLength);
    _count = 0;
    for (decltype(_size) i = 0; i < std::min(_size, rhs._size); ++i){
        _array[i] |= rhs._array[i];
        _count += _BitCount(_array[i]);
    }
    return *this;
}

DynamicBitSet&
DynamicBitSet::operator=(const DynamicBitSet& rhs){
    _array = static_cast<uint32_t*>(realloc(_array, rhs._size));
    _count = rhs._count;
    for (decltype(_size)i = 0; i < _size; ++i) _array[i] = rhs._array[i];
    return *this;
}