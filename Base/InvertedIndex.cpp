#include "InvertedIndex.h"

const uint WITHOUT_4_BITS = 0x0FFFFFFF;

/*
CInvertedIndex::CInvertedIndex(){}
CInvertedIndex::~CInvertedIndex(){}
*/
void
CInvertedIndex::Insert(const std::string& word, uint number)
{
    auto it = _indexes.find(word);
    if (it == _indexes.end())
    {
        it = _indexes.insert(std::make_pair(word, CInvertedIndexElement())).first;
    }
    it->second.Insert(number);
}

void
CInvertedIndex::EncodeAll()
{
    for (auto el : _indexes) el.second.EncodeAll();
}

std::vector< uint >
CInvertedIndex::Get(const std::string& word)
{
    auto it = _indexes.find(word);
    if (it == _indexes.end()) return std::vector< uint >();
    else return it->second.Get();
}

CInvertedIndexElement::CInvertedIndexElement()
: _type (0), _lastValue (0)
{}

CInvertedIndexElement::~CInvertedIndexElement(){}

std::vector< uint >
CInvertedIndexElement::Get()
{
    std::vector<uint> l = Decode();
    uint val = (l.size() ? (*l.end()) : 0), last = 0;
    for (size_t i = 0; i < _tmpValues.size(); ++i)
    {
        last = val;
        val += _tmpValues.front();
        l.push_back(val);
        _tmpValues.pop();
        _tmpValues.push(val - last);
    }
    return l;
}

void
CInvertedIndexElement::EncodeAll()
{
    if (_tmpValues.empty()) return;
    else
    {
        Encode();
    }
}
int Type(int bitLength)
{
    if (bitLength > TYPE_H) return TYPE_I;
    else if (bitLength > TYPE_G) return TYPE_H;
    else if (bitLength > TYPE_F) return TYPE_G;
    else if (bitLength > TYPE_E) return TYPE_F;
    else if (bitLength > TYPE_D) return TYPE_E;
    else if (bitLength > TYPE_C) return TYPE_D;
    else if (bitLength > TYPE_B) return TYPE_C;
    else if (bitLength > TYPE_A) return TYPE_B;
    else return TYPE_A;
}

int BitLength(uint number)
{
    int i = 0;
    for (; number; ++i) number >>= 1;
    return i;
}

inline
int GetType( uint number)
{
    int bitlen = BitLength(number);
    return Type(bitlen);
}

int TypeContain( int type )
{
    return 28 / type;
}

int eTypeToeBin_Type( int type )
{
    switch (type)
    {
        case TYPE_A : return BIN_TYPE_A;
        case TYPE_B : return BIN_TYPE_B;
        case TYPE_C : return BIN_TYPE_C;
        case TYPE_D : return BIN_TYPE_D;
        case TYPE_E : return BIN_TYPE_E;
        case TYPE_F : return BIN_TYPE_F;
        case TYPE_G : return BIN_TYPE_G;
        case TYPE_H : return BIN_TYPE_H;
        case TYPE_I : return BIN_TYPE_I;
    }
    return -1;
}

int eBin_TypeToeType( int type )
{
    switch (type)
    {
        case BIN_TYPE_A : return TYPE_A;
        case BIN_TYPE_B : return TYPE_B;
        case BIN_TYPE_C : return TYPE_C;
        case BIN_TYPE_D : return TYPE_D;
        case BIN_TYPE_E : return TYPE_E;
        case BIN_TYPE_F : return TYPE_F;
        case BIN_TYPE_G : return TYPE_G;
        case BIN_TYPE_H : return TYPE_H;
        case BIN_TYPE_I : return TYPE_I;
    }
    return -1;
}

inline
bool CanAdd( uint value, int type)
{ return value / (1 << (type)) == 0; }

inline
int TypeExtraBits(int type)
{ return 28 % type; }


void
CInvertedIndexElement::Insert(uint value)
{
    if (value == _lastValue) return;
    uint tmp = value - _lastValue;
    uint tmpType = GetType(tmp);
    uint contain = TypeContain(tmpType);
    if (tmpType > _type)
    {
        if (contain < _tmpValues.size() + 1) Encode();
        _type = tmpType;
    }
    _tmpValues.push(tmp);
    if (static_cast<size_t>(TypeContain(_type)) == _tmpValues.size()) Encode();
    _lastValue = value;
}

void 
CInvertedIndexElement::Encode()
{
    uint value = eTypeToeBin_Type(_type),
        contain = TypeContain(_type),
        i;
    uint topValue = _tmpValues.front();

    for (i = 0; i < contain && CanAdd(topValue, _type); ++i)
    {
        value <<= _type;
        value |= topValue;
        _tmpValues.pop();
        if (!_tmpValues.empty()) topValue = _tmpValues.front();
        else
        {
            ++i;
            break;
        }
    }

    value <<= ((contain - i) * _type);
    value <<= TypeExtraBits(_type);
    _encoded.push_back(value);
    if (_tmpValues.empty()) _type = 0;
}

std::vector<uint>
CInvertedIndexElement::Decode()
{
    uint type, value, contain, lastValue = 0,
    leftMove, rightMove;
    std::vector <uint> result;
    for (uint el : _encoded)
    {
        type = eBin_TypeToeType(el >> 28);
        contain = TypeContain(type);
        el >>= TypeExtraBits(type);

        leftMove = 1 << type;
        rightMove = (contain ) * type;
        while(contain--)
        {
            value = (el >> (rightMove -= type)) % leftMove;
            
            if (value)
            {
                result.push_back(lastValue + value);
                lastValue += value;
            } else break;
        }
        // for (count = 0; count != contain; ++count)
        // {
        //     value = el % (1 << type);
        //     el >>= type;
        //     array[(contain - count) - 1] = value;
        // }
        // for (uint i = 0; i < contain; ++i)
        // {
        //     if (array[i] != 0)
        //     {
        //         value = lastValue + array[i];
        //         result.push_back(value);
        //         lastValue = value;
        //     }
        // }
    }
    return result;
}

std::string ToBin(uint v)
{
    std::string s;
    for (int i = 0 ; i < 32; ++i) s += (v & (1 << i) ? '1' : '0');
    std::reverse(s.begin(), s.end());
    return s;
}

void
CInvertedIndex::Print()
{
    for (auto el : _indexes){
        std::cout << el.first << " ";
        el.second.Print();
        std::cout << "\n";
    }
}

void
CInvertedIndexElement::Print()
{
    for (auto el : _encoded)
    {
        std::string s = ToBin(el);
        uint type = eBin_TypeToeType(el >> 28);
        std::cout << type << "\t";
        std::cout << s[0] << s[1] << s[2] << s[3] << " ";
        for (int i = 4; i < 32;){
            for (size_t j = 0; j < type && i < 32; ++j, ++i) std::cout << s[i];
            std:: cout << " ";
        }
        std::cout << "\t";
    }
}