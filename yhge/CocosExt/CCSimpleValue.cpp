#include "CCSimpleValue.h"

NS_CC_YHGE_BEGIN

const SimpleValue SimpleValue::Null;

SimpleValue::SimpleValue()
:_type(NONE)
{
    
}

SimpleValue::SimpleValue(unsigned char v)
:_type(BYTE)
{
    _baseData.byteVal = v;
}

SimpleValue::SimpleValue(int v)
:_type(INTEGER)
{
    _baseData.intVal = v;
}

SimpleValue::SimpleValue(float v)
:_type(FLOAT)
{
    _baseData.floatVal = v;
}

SimpleValue::SimpleValue(double v)
:_type(DOUBLE)
{
    _baseData.doubleVal = v;
}

SimpleValue::SimpleValue(bool v)
:_type(BOOLEAN)
{
    _baseData.boolVal = v;
}

SimpleValue::SimpleValue(const char* v)
:_type(STRING)
{
    _baseData.strVal=new CCString(v);
}

SimpleValue::SimpleValue(const std::string& v)
:_type(STRING)
{
    _baseData.strVal=new CCString(v);
}


SimpleValue::SimpleValue(const SimpleValue& other)
{
    *this = other;
}

SimpleValue::~SimpleValue()
{
    clear();
}

SimpleValue& SimpleValue::operator= (const SimpleValue& other)
{
    if (this != &other) {
        switch (other._type) {
            case BYTE:
                _baseData.byteVal = other._baseData.byteVal;
                break;
            case INTEGER:
                _baseData.intVal = other._baseData.intVal;
                break;
            case FLOAT:
                _baseData.floatVal = other._baseData.floatVal;
                break;
            case DOUBLE:
                _baseData.doubleVal = other._baseData.doubleVal;
                break;
            case BOOLEAN:
                _baseData.boolVal = other._baseData.boolVal;
                break;
            case STRING:
                _baseData.strVal=other._baseData.strVal;
                _baseData.strVal->retain();
                break;
            default:
                break;
        }
        _type = other._type;
    }
    return *this;
}

SimpleValue& SimpleValue::operator= (unsigned char v)
{
    clear();
    _type = BYTE;
    _baseData.byteVal = v;
    return *this;
}

SimpleValue& SimpleValue::operator= (int v)
{
    clear();
    _type = INTEGER;
    _baseData.intVal = v;
    return *this;
}

SimpleValue& SimpleValue::operator= (float v)
{
    clear();
    _type = FLOAT;
    _baseData.floatVal = v;
    return *this;
}

SimpleValue& SimpleValue::operator= (double v)
{
    clear();
    _type = DOUBLE;
    _baseData.doubleVal = v;
    return *this;
}

SimpleValue& SimpleValue::operator= (bool v)
{
    clear();
    _type = BOOLEAN;
    _baseData.boolVal = v;
    return *this;
}

SimpleValue& SimpleValue::operator= (const char* v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new CCString(v);
    return *this;
}

SimpleValue& SimpleValue::operator= (const std::string& v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new CCString(v);
    return *this;
}

///
unsigned char SimpleValue::asByte() const
{
    if (_type == BYTE)
    {
        return _baseData.byteVal;
    }
    
    if (_type == INTEGER)
    {
        return static_cast<unsigned char>(_baseData.intVal);
    }
    
    if (_type == STRING)
    {
        return static_cast<unsigned char>(_baseData.strVal->intValue());
    }
    
    if (_type == FLOAT)
    {
        return static_cast<unsigned char>(_baseData.floatVal);
    }
    
    if (_type == DOUBLE)
    {
        return static_cast<unsigned char>(_baseData.doubleVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1 : 0;
    }
    
    return 0;
}

int SimpleValue::asInt() const
{
    if (_type == INTEGER)
    {
        return _baseData.intVal;
    }
    
    if (_type == BYTE)
    {
        return _baseData.byteVal;
    }
    
    if (_type == STRING)
    {
        return _baseData.strVal->intValue();
    }
    
    if (_type == FLOAT)
    {
        return static_cast<int>(_baseData.floatVal);
    }
    
    if (_type == DOUBLE)
    {
        return static_cast<int>(_baseData.doubleVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1 : 0;
    }
    
    return 0;
}

float SimpleValue::asFloat() const
{
    if (_type == FLOAT)
    {
        return _baseData.floatVal;
    }
    
    if (_type == BYTE)
    {
        return static_cast<float>(_baseData.byteVal);
    }
    
    if (_type == STRING)
    {
        return _baseData.strVal->floatValue();
    }
    
    if (_type == INTEGER)
    {
        return static_cast<float>(_baseData.intVal);
    }
    
    if (_type == DOUBLE)
    {
        return static_cast<float>(_baseData.doubleVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1.0f : 0.0f;
    }
    
    return 0.0f;
}

double SimpleValue::asDouble() const
{
    if (_type == DOUBLE)
    {
        return _baseData.doubleVal;
    }
    
    if (_type == BYTE)
    {
        return static_cast<double>(_baseData.byteVal);
    }
    
    if (_type == STRING)
    {
        return _baseData.strVal->doubleValue();
    }
    
    if (_type == INTEGER)
    {
        return static_cast<double>(_baseData.intVal);
    }
    
    if (_type == FLOAT)
    {
        return static_cast<double>(_baseData.floatVal);
    }
    
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal ? 1.0 : 0.0;
    }
    
    return 0.0;
}

bool SimpleValue::asBool() const
{
    if (_type == BOOLEAN)
    {
        return _baseData.boolVal;
    }
    
    if (_type == BYTE)
    {
        return _baseData.byteVal == 0 ? false : true;
    }
    
    if (_type == STRING)
    {
        std::string val=_baseData.strVal->getCString();
        return (val == "0" || val == "false") ? false : true;
    }
    
    if (_type == INTEGER)
    {
        return _baseData.intVal == 0 ? false : true;
    }
    
    if (_type == FLOAT)
    {
        return _baseData.floatVal == 0.0f ? false : true;
    }
    
    if (_type == DOUBLE)
    {
        return _baseData.doubleVal == 0.0 ? false : true;
    }
    
    return true;
}

std::string SimpleValue::asString() const
{
    if (_type == STRING)
    {
        return _baseData.strVal->getCString();
    }
    
    std::stringstream ret;
    
    switch (_type) {
        case BYTE:
            ret << _baseData.byteVal;
            break;
        case INTEGER:
            ret << _baseData.intVal;
            break;
        case FLOAT:
            ret << _baseData.floatVal;
            break;
        case DOUBLE:
            ret << _baseData.doubleVal;
            break;
        case BOOLEAN:
            ret << (_baseData.boolVal ? "true" : "false");
            break;
        default:
            break;
    }
    return ret.str();
}

static std::string getTabs(int depth)
{
    std::string tabWidth;
    
    for (int i = 0; i < depth; ++i)
    {
        tabWidth += "\t";
    }
    
    return tabWidth;
}

static std::string visit(const SimpleValue& v, int depth)
{
    std::stringstream ret;

    switch (v.getType())
    {
        case SimpleValue::NONE:
        case SimpleValue::BYTE:
        case SimpleValue::INTEGER:
        case SimpleValue::FLOAT:
        case SimpleValue::DOUBLE:
        case SimpleValue::BOOLEAN:
        case SimpleValue::STRING:
            ret << v.asString() << "\n";
            break;
        default:
            CCAssert(false, "Invalid type!");
            break;
    }
    
    return ret.str();
}

std::string SimpleValue::getDescription()
{
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void SimpleValue::clear()
{
    if (_type==STRING) {
        _baseData.strVal->release();
    }
    
    _type = NONE;
    _baseData.doubleVal = 0.0;
}

NS_CC_YHGE_END
