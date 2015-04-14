#include "InputStream.h"
#include <string>

NS_CC_YHGE_BEGIN

InputStream::InputStream()
:_pos(0)
,_buffer(NULL)
,_endianness(kLittleEndian)
{
    
}

InputStream::~InputStream()
{
    CC_SAFE_RELEASE_NULL(_buffer);
}

bool InputStream::init()
{
    return true;
}

bool InputStream::init(Buffer* buffer)
{
    setBuffer(buffer);
    return true;
}

bool InputStream::initWithStream(InputStream* stream)
{
    if (stream!=this) {
        setBuffer(stream->getBuffer());
        
        return true;
    }
    
    return false;
}

size_t InputStream::readBytes(void* buf,size_t size)
{
    size_t readSize=_buffer->readBytes(_pos, buf, size);
    _pos+=readSize;
    
    return readSize;
}

unsigned char InputStream::readByte()
{
    return _buffer->readByte(_pos++);
}

uint8_t InputStream::readUInt8()
{
    return _buffer->readUInt8(_pos++);
}

uint16_t InputStream::readUInt16()
{
    uint16_t ret= _endianness==kLittleEndian?_buffer->readUInt16LE(_pos):_buffer->readUInt16BE(_pos);
    _pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

uint32_t InputStream::readUInt32()
{
    uint32_t ret= _endianness==kLittleEndian?_buffer->readUInt32LE(_pos):_buffer->readUInt32BE(_pos);
    _pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

uint64_t InputStream::readUInt64()
{
    uint64_t ret= _endianness==kLittleEndian?_buffer->readUInt64LE(_pos):_buffer->readUInt64BE(_pos);
    _pos+=_BUFFER_LONG_SIZE;
    
    return ret;
}

int8_t InputStream::readInt8()
{
    return _buffer->readInt8(_pos++);
}

int16_t InputStream::readInt16()
{
    int16_t ret= _endianness==kLittleEndian?_buffer->readInt16LE(_pos):_buffer->readInt16BE(_pos);
    _pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

int32_t InputStream::readInt32()
{
    int32_t ret= _endianness==kLittleEndian?_buffer->readInt32LE(_pos):_buffer->readInt32BE(_pos);
    _pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

int64_t InputStream::readInt64()
{
    int64_t ret= _endianness==kLittleEndian?_buffer->readInt64LE(_pos):_buffer->readInt64BE(_pos);
    _pos+=_BUFFER_LONG_SIZE;
    
    return ret;
}

float InputStream::readHalfFloat()
{
    float ret= _endianness==kLittleEndian?_buffer->readFloat16LE(_pos):_buffer->readFloat16BE(_pos);
    _pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

float InputStream::readFloat()
{
    float ret= _endianness==kLittleEndian?_buffer->readFloatLE(_pos):_buffer->readFloatBE(_pos);
    _pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

double InputStream::readDouble()
{
    float ret= _endianness==kLittleEndian?_buffer->readDoubleLE(_pos):_buffer->readDoubleBE(_pos);
    _pos+=_BUFFER_LONG_SIZE;
    
    return ret;
}

float InputStream::readHalfFixed()
{
    float ret= _endianness==kLittleEndian?_buffer->readFixed8LE(_pos):_buffer->readFixed8BE(_pos);
    _pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

float InputStream::readFixed()
{
    float ret= _endianness==kLittleEndian?_buffer->readFixedLE(_pos):_buffer->readFixedBE(_pos);
    _pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

void InputStream::seek(size_t lenght)
{
    _pos+=lenght;
}

bool InputStream::eof()
{
    return _pos >= _buffer->getSize();
}

NS_CC_YHGE_END
