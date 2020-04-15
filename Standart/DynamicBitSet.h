#ifndef DYNAMIC_BIT_SET
#define DYNAMIC_BIT_SET

#include <bits/stdc++.h>
#include <cmath>
#include <vector>


const uint32_t ONES32 = 0xffffffff;

class DynamicBitSet
{
public:
    DynamicBitSet(const DynamicBitSet&);
    DynamicBitSet(const DynamicBitSet&&);
    DynamicBitSet(size_t size = 1);
    ~DynamicBitSet();

    inline void
    Set(size_t index)
    {   if ((_array[_DivChunk(index)] & static_cast<uint32_t>( 1 ) << _ModChunk(index)) == 0){
            _array[_DivChunk(index)] |= static_cast<uint32_t>( 1 ) << _ModChunk(index);
            ++_count;
    }}

    inline void
    Reset(size_t index)
    { 
        if ((_array[_DivChunk(index)] & static_cast<uint32_t>( 1 ) << _ModChunk(index)) != 0){
            _array[_DivChunk(index)] &= ONES32 ^ ( static_cast<uint32_t>( 1 ) << _ModChunk(index)); 
            --_count;
        }
    }

    inline bool
    Get(size_t index)
    { return ( index < _bitLength ? _array[_DivChunk(index)] & (static_cast<uint32_t>( 1 ) << (_ModChunk(index))) : 0);}

    inline size_t Size()
    { return _bitLength;}

    inline size_t Count()
    { return _count; }

    std::vector<uint32_t> ToVector();

    void Not(size_t maxSize);


    DynamicBitSet& operator&=(const DynamicBitSet& rhs);
    DynamicBitSet& operator|=(const DynamicBitSet& rhs);
    DynamicBitSet& operator=(const DynamicBitSet& rhs);

private:
    inline size_t _DivChunk(size_t num)
    { return num >> ( _ChunkPow() + 1); }
    inline size_t _ModChunk(size_t num)
    { return num % ( _ChunkLength() ); }
    inline size_t _ChunkPow()
    { return sizeof (uint32_t); }
    inline size_t _ChunkLength()
    { return (_ChunkPow() << 3); }
    size_t _BitCount(uint);

    uint32_t *_array, _size, _bitLength, _count;
};


#endif // DYNAMIC_BIT_SET
