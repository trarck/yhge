#include "OutputStream.h"
#include <string>

NS_CC_YHGE_BEGIN

OutputStream::OutputStream()
:m_pos(0)
,m_buffer(NULL)
,m_endianness(kLittleEndian)
{
    
}

OutputStream::~OutputStream()
{
    CC_SAFE_RELEASE_NULL(m_buffer);
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
    m_pos+=m_buffer->writeBytes(m_pos, buf, size);
}

void OutputStream::writeByte(unsigned char value)
{
    m_pos+=m_buffer->writeByte(value,m_pos);
}

void OutputStream::writeUInt8(uint8_t value)
{
    m_pos+=m_buffer->writeUInt8(value,m_pos);
}

void OutputStream::writeUInt16(uint16_t value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeUInt16LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeUInt16BE(value,m_pos);
    }
}

void OutputStream::writeUInt32(uint32_t value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeUInt32LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeUInt32BE(value,m_pos);
    }
}

void OutputStream::writeUInt64(uint64_t value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeUInt64LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeUInt64BE(value,m_pos);
    }
}

void OutputStream::writeInt8(int8_t value)
{
    m_pos+=m_buffer->writeInt8(value,m_pos);
}

void OutputStream::writeInt16(int16_t value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeInt16LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeInt16BE(value,m_pos);
    }
}

void OutputStream::writeInt32(int32_t value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeInt32LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeInt32BE(value,m_pos);
    }
}

void OutputStream::writeInt64(int64_t value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeInt64LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeInt64BE(value,m_pos);
    }
}

void OutputStream::writeHalfFloat(float value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeFloat16LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeFloat16BE(value,m_pos);
    }
}

void OutputStream::writeFloat(float value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeFloatLE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeFloatBE(value,m_pos);
    }
}

void OutputStream::writeDouble(double value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeDoubleLE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeDoubleBE(value,m_pos);
    }
}

void OutputStream::writeHalfFixed(float value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeFixed8LE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeFixed8BE(value,m_pos);
    }
}

void OutputStream::writeFixed(float value)
{
    if (m_endianness==kLittleEndian) {
        m_pos+=m_buffer->writeFixedLE(value,m_pos);
    }else{
        m_pos+=m_buffer->writeFixedBE(value,m_pos);
    }
}

void OutputStream::seek(size_t lenght)
{
    m_pos+=lenght;
}

bool OutputStream::eof()
{
    return m_pos>=m_buffer->getSize();
}

NS_CC_YHGE_END
