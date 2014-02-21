#include "CCValue.h"
#include <sstream>

NS_CC_YHGE_BEGIN

const Value Value::Null;

Value::Value()
: _vectorData(new ValueVector())
, _mapData(new ValueMap())
, _intKeyMapData(new ValueMapIntKey())
, _type(NONE)
{
    
}

Value::Value(unsigned char v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(BYTE)
{
    _baseData.byteVal = v;
}

Value::Value(int v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(INTEGER)
{
    _baseData.intVal = v;
}

Value::Value(float v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(FLOAT)
{
    _baseData.floatVal = v;
}

Value::Value(double v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(DOUBLE)
{
    _baseData.doubleVal = v;
}

Value::Value(bool v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(BOOLEAN)
{
    _baseData.boolVal = v;
}

Value::Value(const char* v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(STRING)
{
    _strData = v;
}

Value::Value(const std::string& v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(STRING)
{
    _strData = v;
}

Value::Value(const ValueVector& v)
: _vectorData(new ValueVector())
, _mapData(NULL)
, _intKeyMapData(NULL)
, _type(VECTOR)
{
    *_vectorData = v;
}

Value::Value(const ValueMap& v)
: _vectorData(NULL)
, _mapData(new ValueMap())
, _intKeyMapData(NULL)
, _type(MAP)
{
    *_mapData = v;
}

Value::Value(const ValueMapIntKey& v)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(new ValueMapIntKey())
, _type(INT_KEY_MAP)
{
    *_intKeyMapData = v;
}

Value::Value(const Value& other)
: _vectorData(NULL)
, _mapData(NULL)
, _intKeyMapData(NULL)
{
    *this = other;
}

Value::~Value()
{
    clear();
}

Value& Value::operator= (const Value& other)
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
                _strData = other._strData;
                break;
            case VECTOR:
                if (_vectorData == NULL)
                    _vectorData = new ValueVector();
                *_vectorData = *other._vectorData;
                break;
            case MAP:
                if (_mapData == NULL)
                    _mapData = new ValueMap();
                *_mapData = *other._mapData;
                break;
            case INT_KEY_MAP:
                if (_intKeyMapData == NULL)
                    _intKeyMapData = new ValueMapIntKey();
                *_intKeyMapData = *other._intKeyMapData;
                break;
            default:
                break;
        }
        _type = other._type;
    }
    return *this;
}

Value& Value::operator= (unsigned char v)
{
    clear();
    _type = BYTE;
    _baseData.byteVal = v;
    return *this;
}

Value& Value::operator= (int v)
{
    clear();
    _type = INTEGER;
    _baseData.intVal = v;
    return *this;
}

Value& Value::operator= (float v)
{
    clear();
    _type = FLOAT;
    _baseData.floatVal = v;
    return *this;
}

Value& Value::operator= (double v)
{
    clear();
    _type = DOUBLE;
    _baseData.doubleVal = v;
    return *this;
}

Value& Value::operator= (bool v)
{
    clear();
    _type = BOOLEAN;
    _baseData.boolVal = v;
    return *this;
}

Value& Value::operator= (const char* v)
{
    clear();
    _type = STRING;
    _strData = v ? v : "";
    return *this;
}

Value& Value::operator= (const std::string& v)
{
    clear();
    _type = STRING;
    _strData = v;
    return *this;
}

Value& Value::operator= (const ValueVector& v)
{
    clear();
    _type = VECTOR;
    _vectorData = new ValueVector();
    *_vectorData = v;
    return *this;
}

Value& Value::operator= (const ValueMap& v)
{
    clear();
    _type = MAP;
    _mapData = new ValueMap();
    *_mapData = v;
    return *this;
}

Value& Value::operator= (const ValueMapIntKey& v)
{
    clear();
    _type = INT_KEY_MAP;
    _intKeyMapData = new ValueMapIntKey();
    *_intKeyMapData = v;
    return *this;
}

///
unsigned char Value::asByte() const
{
    CCAssert(_type != VECTOR && _type != MAP, "");
    
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
        return static_cast<unsigned char>(atoi(_strData.c_str()));
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

int Value::asInt() const
{
    CCAssert(_type != VECTOR && _type != MAP, "");
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
        return atoi(_strData.c_str());
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

float Value::asFloat() const
{
    CCAssert(_type != VECTOR && _type != MAP, "");
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
        return atof(_strData.c_str());
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

double Value::asDouble() const
{
    CCAssert(_type != VECTOR && _type != MAP, "");
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
        return static_cast<double>(atof(_strData.c_str()));
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

bool Value::asBool() const
{
    CCAssert(_type != VECTOR && _type != MAP, "");
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
        return (_strData == "0" || _strData == "false") ? false : true;
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

std::string Value::asString() const
{
    CCAssert(_type != VECTOR && _type != MAP, "");
    
    if (_type == STRING)
    {
        return _strData;
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

ValueVector& Value::asValueVector()
{
	if (NULL == _vectorData)
		_vectorData = new ValueVector();
	return *_vectorData;
}

const ValueVector& Value::asValueVector() const
{
	static const ValueVector EMPTY_VALUEVECTOR;
	if (NULL == _vectorData)
		return EMPTY_VALUEVECTOR;
	return *_vectorData; 
}

ValueMap& Value::asValueMap()
{
	if (NULL == _mapData)
		_mapData = new ValueMap();
	return *_mapData;
}

const ValueMap& Value::asValueMap() const
{
	static const ValueMap EMPTY_VALUEMAP;
	if (NULL == _mapData)
		return EMPTY_VALUEMAP;
	return *_mapData;
}

ValueMapIntKey& Value::asIntKeyMap()
{
	if (NULL == _intKeyMapData)
		_intKeyMapData = new ValueMapIntKey();
	return *_intKeyMapData;
}

const ValueMapIntKey& Value::asIntKeyMap() const
{
	static const ValueMapIntKey EMPTY_VALUEMAP_INT_KEY;
	if (NULL == _intKeyMapData)
		return EMPTY_VALUEMAP_INT_KEY;
	return *_intKeyMapData;
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

static std::string visit(const Value& v, int depth);

static std::string visitVector(const ValueVector& v, int depth)
{
    std::stringstream ret;
    
    if (depth > 0)
        ret << "\n";
    
    ret << getTabs(depth) << "[\n";
    
    int i = 0;
    for (const auto& child : v)
    {
        ret << getTabs(depth+1) << i << ": " << visit(child, depth + 1);
        ++i;
    }
    
    ret << getTabs(depth) << "]\n";
    
    return ret.str();
}

template <class T>
static std::string visitMap(const T& v, int depth)
{
    std::stringstream ret;
    
    if (depth > 0)
        ret << "\n";
    
    ret << getTabs(depth) << "{\n";
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        ret << getTabs(depth + 1) << iter->first << ": ";
        ret << visit(iter->second, depth + 1);
    }
    
    ret << getTabs(depth) << "}\n";
    
    return ret.str();
}

static std::string visit(const Value& v, int depth)
{
    std::stringstream ret;

    switch (v.getType())
    {
        case Value::NONE:
        case Value::BYTE:
        case Value::INTEGER:
        case Value::FLOAT:
        case Value::DOUBLE:
        case Value::BOOLEAN:
        case Value::STRING:
            ret << v.asString() << "\n";
            break;
        case Value::VECTOR:
            ret << visitVector(v.asValueVector(), depth);
            break;
        case Value::MAP:
            ret << visitMap(v.asValueMap(), depth);
            break;
        case Value::INT_KEY_MAP:
            ret << visitMap(v.asIntKeyMap(), depth);
            break;
        default:
            CCAssert(false, "Invalid type!");
            break;
    }
    
    return ret.str();
}

std::string Value::getDescription()
{
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void Value::clear()
{
    _type = NONE;
    _baseData.doubleVal = 0.0;
    _strData.clear();
    CC_SAFE_DELETE(_vectorData);
    CC_SAFE_DELETE(_mapData);
    CC_SAFE_DELETE(_intKeyMapData);
}

NS_CC_YHGE_END
