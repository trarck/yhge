#include "OutputStream.h"
#include <string>

NS_CC_YHGE_BEGIN

OutputStream::OutputStream()
:_pos(0)
,_buffer(NULL)
,_endianness(kLittleEndian)
{
    
}

OutputStream::~OutputStream()
{
    CC_SAFE_RELEASE_NULL(_buffer);
}

bool OutputStream::init()
{
    return true;
}

bool OutputStream::init(Buffer* buffer)
{
    setBuffer(buffer);
    return true;
}

bool OutputStream::initWithStream(OutputStream* stream)
{
    if (stream!=this) {
        setBuffer(stream->getBuffer());
        return true;
    }
    
    return false;
}

void OutputStream::writeBytes(void* buf,size_t size)
{
    _pos+=_buffer->writeBytes(_pos, buf, size);
}

void OutputStream::writeByte(unsigned char value)
{
    _pos+=_buffer->writeByte(value,_pos);
}

void OutputStream::writeUInt8(uint8_t value)
{
    _pos+=_buffer->writeUInt8(value,_pos);
}

void OutputStream::writeUInt16(uint16_t value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeUInt16LE(value,_pos);
    }else{
        _pos+=_buffer->writeUInt16BE(value,_pos);
    }
}

void OutputStream::writeUInt32(uint32_t value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeUInt32LE(value,_pos);
    }else{
        _pos+=_buffer->writeUInt32BE(value,_pos);
    }
}

void OutputStream::writeUInt64(uint64_t value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeUInt64LE(value,_pos);
    }else{
        _pos+=_buffer->writeUInt64BE(value,_pos);
    }
}

void OutputStream::writeInt8(int8_t value)
{
    _pos+=_buffer->writeInt8(value,_pos);
}

void OutputStream::writeInt16(int16_t value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeInt16LE(value,_pos);
    }else{
        _pos+=_buffer->writeInt16BE(value,_pos);
    }
}

void OutputStream::writeInt32(int32_t value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeInt32LE(value,_pos);
    }else{
        _pos+=_buffer->writeInt32BE(value,_pos);
    }
}

void OutputStream::writeInt64(int64_t value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeInt64LE(value,_pos);
    }else{
        _pos+=_buffer->writeInt64BE(value,_pos);
    }
}

void OutputStream::writeHalfFloat(float value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeFloat16LE(value,_pos);
    }else{
        _pos+=_buffer->writeFloat16BE(value,_pos);
    }
}

void OutputStream::writeFloat(float value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeFloatLE(value,_pos);
    }else{
        _pos+=_buffer->writeFloatBE(value,_pos);
    }
}

void OutputStream::writeDouble(double value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeDoubleLE(value,_pos);
    }else{
        _pos+=_buffer->writeDoubleBE(value,_pos);
    }
}

void OutputStream::writeHalfFixed(float value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeFixed8LE(value,_pos);
    }else{
        _pos+=_buffer->writeFixed8BE(value,_pos);
    }
}

void OutputStream::writeFixed(float value)
{
    if (_endianness==kLittleEndian) {
        _pos+=_buffer->writeFixedLE(value,_pos);
    }else{
        _pos+=_buffer->writeFixedBE(value,_pos);
    }
}

void OutputStream::seek(size_t lenght)
{
    _pos+=lenght;
}

bool OutputStream::eof()
{
    return _pos>=_buffer->getSize();
}

NS_CC_YHGE_END
