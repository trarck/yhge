#include "CocosValue.h"

NS_CC_YHGE_BEGIN

const CocosValue CocosValue::Null;

CocosValue::CocosValue()
:_type(NONE)
{
    
}

CocosValue::CocosValue(unsigned char v)
:_type(BYTE)
{
    _baseData.byteVal = v;
}

CocosValue::CocosValue(int v)
:_type(INTEGER)
{
    _baseData.intVal = v;
}

CocosValue::CocosValue(float v)
:_type(FLOAT)
{
    _baseData.floatVal = v;
}

CocosValue::CocosValue(double v)
:_type(DOUBLE)
{
    _baseData.doubleVal = v;
}

CocosValue::CocosValue(bool v)
:_type(BOOLEAN)
{
    _baseData.boolVal = v;
}

CocosValue::CocosValue(const char* v)
:_type(STRING)
{
    _baseData.strVal=new CCString(v);
}

CocosValue::CocosValue(const std::string& v)
:_type(STRING)
{
    _baseData.strVal=new CCString(v);
}

CocosValue::CocosValue(const ValueVector& v)
:_type(VECTOR)
{
    _baseData.vectorVal=new ValueVector();
    *(_baseData.vectorVal) = v;
}

CocosValue::CocosValue(const ValueMap& v)
:_type(MAP)
{
    _baseData.mapVal=new ValueMap();
    *(_baseData.mapVal) = v;
}

CocosValue::CocosValue(const ValueMapIntKey& v)
:_type(INT_KEY_MAP)
{
    _baseData.intKeyMapVal=new ValueMapIntKey();
    *(_baseData.intKeyMapVal) = v;
}

CocosValue::CocosValue(const CocosValue& other)
{
    *this = other;
}

CocosValue::~CocosValue()
{
    clear();
}

CocosValue& CocosValue::operator= (const CocosValue& other)
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
                
            case VECTOR:
                if (_baseData.vectorVal == NULL)
                    _baseData.vectorVal = new ValueVector();
                *(_baseData.vectorVal) = *(other._baseData.vectorVal);
                break;
            case MAP:
                if (_baseData.mapVal == NULL)
                    _baseData.mapVal = new ValueMap();
                *(_baseData.mapVal) = *(other._baseData.mapVal);
                break;
            case INT_KEY_MAP:
                if (_baseData.intKeyMapVal == NULL)
                    _baseData.intKeyMapVal = new ValueMapIntKey();
                *(_baseData.intKeyMapVal) = *(other._baseData.intKeyMapVal);
                break;

            default:
                break;
        }
        _type = other._type;
    }
    return *this;
}

CocosValue& CocosValue::operator= (unsigned char v)
{
    clear();
    _type = BYTE;
    _baseData.byteVal = v;
    return *this;
}

CocosValue& CocosValue::operator= (int v)
{
    clear();
    _type = INTEGER;
    _baseData.intVal = v;
    return *this;
}

CocosValue& CocosValue::operator= (float v)
{
    clear();
    _type = FLOAT;
    _baseData.floatVal = v;
    return *this;
}

CocosValue& CocosValue::operator= (double v)
{
    clear();
    _type = DOUBLE;
    _baseData.doubleVal = v;
    return *this;
}

CocosValue& CocosValue::operator= (bool v)
{
    clear();
    _type = BOOLEAN;
    _baseData.boolVal = v;
    return *this;
}

CocosValue& CocosValue::operator= (const char* v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new CCString(v);
    return *this;
}

CocosValue& CocosValue::operator= (const std::string& v)
{
    clear();
    _type = STRING;
    _baseData.strVal=new CCString(v);
    return *this;
}


CocosValue& CocosValue::operator= (const ValueVector& v)
{
    clear();
    _type = VECTOR;
    _baseData.vectorVal = new ValueVector();
    *(_baseData.vectorVal) = v;
    return *this;
}

CocosValue& CocosValue::operator= (const ValueMap& v)
{
    clear();
    _type = MAP;
    _baseData.mapVal = new ValueMap();
    *(_baseData.mapVal) = v;
    return *this;
}

CocosValue& CocosValue::operator= (const ValueMapIntKey& v)
{
    clear();
    _type = INT_KEY_MAP;
    _baseData.intKeyMapVal = new ValueMapIntKey();
    *(_baseData.intKeyMapVal) = v;
    return *this;
}

///
unsigned char CocosValue::asByte() const
{
    CCAssert(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to byte");
    
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

int CocosValue::asInt() const
{
    CCAssert(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to int");
    
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

float CocosValue::asFloat() const
{
    CCAssert(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to float");
    
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

double CocosValue::asDouble() const
{
    CCAssert(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to double");
    
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

bool CocosValue::asBool() const
{
    CCAssert(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to bool");
    
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

std::string CocosValue::asString() const
{
    CCAssert(_type!=VECTOR && _type!=MAP && _type!=INT_KEY_MAP, "can't covert from vector or map to string");
    
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

CocosValue::ValueVector& CocosValue::asValueVector()
{
    CCAssert(_type==VECTOR || _type==NONE, "CocosValue::asValueVector _type is not vector");
    
	if (_type==NONE){
		clear();
        _type=VECTOR;
        _baseData.vectorVal=new ValueVector();
    }
    
	return *(_baseData.vectorVal);
}

const CocosValue::ValueVector& CocosValue::asValueVector() const
{
    CCAssert(_type==VECTOR || _type==NONE, "CocosValue::asValueVector _type is not vector");
    
	static const ValueVector EMPTY_VALUEVECTOR;
	if (NONE == _type)
		return EMPTY_VALUEVECTOR;
	return *(_baseData.vectorVal);
}

CocosValue::ValueMap& CocosValue::asValueMap()
{
    CCAssert(_type==MAP || _type==NONE, "CocosValue::asValueVector _type is not map");
	if (NONE == _type){
        _type=MAP;
		_baseData.mapVal = new ValueMap();
    }
	return *(_baseData.mapVal);
}

const CocosValue::ValueMap& CocosValue::asValueMap() const
{
    CCAssert(_type==MAP || _type==NONE, "CocosValue::asValueVector _type is not map");
    
	static const ValueMap EMPTY_VALUEMAP;
	if (NONE == _type)
		return EMPTY_VALUEMAP;
	return *(_baseData.mapVal);
}

CocosValue::ValueMapIntKey& CocosValue::asIntKeyMap()
{
    CCAssert(_type==INT_KEY_MAP || _type==NONE, "CocosValue::asValueVector _type is not map");
    
	if (NONE == _type){
        _type=INT_KEY_MAP;
		_baseData.intKeyMapVal = new ValueMapIntKey();
    }
	return *(_baseData.intKeyMapVal);
}

const CocosValue::ValueMapIntKey& CocosValue::asIntKeyMap() const
{
	static const ValueMapIntKey EMPTY_VALUEMAP_INT_KEY;
	if (NONE == _type)
		return EMPTY_VALUEMAP_INT_KEY;
	return *(_baseData.intKeyMapVal);
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

static std::string visit(const CocosValue& v, int depth)
{
    std::stringstream ret;

    switch (v.getType())
    {
        case CocosValue::NONE:
        case CocosValue::BYTE:
        case CocosValue::INTEGER:
        case CocosValue::FLOAT:
        case CocosValue::DOUBLE:
        case CocosValue::BOOLEAN:
        case CocosValue::STRING:
            ret << v.asString() << "\n";
            break;
        default:
            CCAssert(false, "Invalid type!");
            break;
    }
    
    return ret.str();
}

std::string CocosValue::getDescription()
{
    std::string ret("\n");
    ret += visit(*this, 0);
    return ret;
}

void CocosValue::clear()
{
    
    switch (_type) {
        case STRING:
            _baseData.strVal->release();
            break;
        case VECTOR:
            CC_SAFE_DELETE(_baseData.vectorVal);
            break;
        case MAP:
            CC_SAFE_DELETE(_baseData.mapVal);
            break;
        case INT_KEY_MAP:
            CC_SAFE_DELETE(_baseData.intKeyMapVal);
            break;
        default:
            break;
    }
    
    _type = NONE;
    _baseData.doubleVal = 0.0;
}

NS_CC_YHGE_END
