#ifndef DYNAMIC_BIT_SET
#define DYNAMIC_BIT_SET

#include <bits/stdc++.h>
#include <cmath>


const uint32_t ONES32 = 0xffffffff;

class DynamicBitSet
{
public:
    DynamicBitSet(const DynamicBitSet&);
    DynamicBitSet(const DynamicBitSet&&);
    DynamicBitSet(size_t size = 1);
    ~DynamicBitSet();

    // void Set(size_t index);

    inline void
    Set(size_t index)
    { _array[_DivChunk(index)] |= static_cast<uint32_t>( 1 ) << _ModChunk(index); }

    inline void
    Reset(size_t index)
    { _array[_DivChunk(index)] &= ONES32 ^ ( static_cast<uint32_t>( 1 ) << _ModChunk(index)); }

    inline bool
    Get(size_t index)
    { return ( index < _bitLength ? _array[_DivChunk(index)] & (static_cast<uint32_t>( 1 ) << (_ModChunk(index))) : 0);}

    inline size_t Size()
    { return _bitLength;}

    void Not(size_t maxSize);


    DynamicBitSet& operator&=(const DynamicBitSet& rhs);
    DynamicBitSet& operator|=(const DynamicBitSet& rhs);
    DynamicBitSet& operator=(const DynamicBitSet& rhs);

private:
    size_t _DivChunk(size_t num)
    { return num >> ( _ChunkPow() ); }
    size_t _ModChunk(size_t num)
    { return num % ( _ChunkLength() ); }
    int _ChunkPow(){
        return sizeof (uint32_t) + 1;
    }
    int _ChunkLength()
    { return (1 << _ChunkPow()); }

    uint32_t *_array, _size, _bitLength;
};


#endif // DYNAMIC_BIT_SET
