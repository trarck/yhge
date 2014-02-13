#ifndef YHGE_COCOSEXT_SUPPORT_CCVALUE_H_
#define YHGE_COCOSEXT_SUPPORT_CCVALUE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include <string>
#include <vector>

#if USE_STD_UNORDERED_MAP
#include <unordered_map>
#else
#include <map>
#endif

NS_CC_YHGE_BEGIN

class Value;

typedef std::vector<Value> ValueVector;

#if USE_STD_UNORDERED_MAP
	typedef std::unordered_map<std::string, Value> ValueMap;
	typedef std::unordered_map<int, Value> ValueMapIntKey;
#else
	typedef std::map<std::string, Value> ValueMap;
	typedef std::map<int, Value> ValueMapIntKey;
#endif

class Value
{
public:
    static const Value Null;
    
    Value();
    explicit Value(unsigned char v);
    explicit Value(int v);
    explicit Value(float v);
    explicit Value(double v);
    explicit Value(bool v);
    explicit Value(const char* v);
    explicit Value(const std::string& v);
    
    explicit Value(const ValueVector& v);
    explicit Value(ValueVector&& v);
    
    explicit Value(const ValueMap& v);
	explicit Value(ValueMap&& v);
    
    explicit Value(const ValueMapIntKey& v);
    explicit Value(ValueMapIntKey&& v);
    
    Value(const Value& other);
    Value(Value&& other);
    ~Value();
    
    // assignment operator
    Value& operator= (const Value& other);
    Value& operator= (Value&& other);
    
    Value& operator= (unsigned char v);
    Value& operator= (int v);
    Value& operator= (float v);
    Value& operator= (double v);
    Value& operator= (bool v);
    Value& operator= (const char* v);
    Value& operator= (const std::string& v);
    
    Value& operator= (const ValueVector& v);
    Value& operator= (ValueVector&& v);
    
    Value& operator= (const ValueMap& v);
	Value& operator= (ValueMap&& v);
    
    Value& operator= (const ValueMapIntKey& v);
    Value& operator= (ValueMapIntKey&& v);
    
    unsigned char asByte() const;
    int asInt() const;
    float asFloat() const;
    double asDouble() const;
    bool asBool() const;
    std::string asString() const;
    
    ValueVector& asValueVector();
    const ValueVector& asValueVector() const;
    
    ValueMap& asValueMap();
    const ValueMap& asValueMap() const;
    
    ValueMapIntKey& asIntKeyMap();
    const ValueMapIntKey& asIntKeyMap() const;

    inline bool isNull() const { return _type == Type::NONE; }
    
    enum class Type
    {
        NONE,
        BYTE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
        VECTOR,
        MAP,
        INT_KEY_MAP
    };

    inline Type getType() const { return _type; };
    
    std::string getDescription();
    
private:
    void clear();
    
    union
    {
        unsigned char byteVal;
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;
    }_baseData;
    
    std::string _strData;
    ValueVector* _vectorData;
    ValueMap* _mapData;
    ValueMapIntKey* _intKeyMapData;

    Type _type;
};

NS_CC_YHGE_END


#endif /* defined(YHGE_COCOSEXT_SUPPORT_CCVALUE_H_) */
