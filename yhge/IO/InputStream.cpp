#include "InputStream.h"
#include <string>

NS_CC_YHGE_BEGIN

InputStream::InputStream()
:m_pos(0)
,m_buffer(NULL)
,m_endianness(kLittleEndian)
{
    
}

InputStream::~InputStream()
{
    CC_SAFE_RELEASE_NULL(m_buffer);
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
    size_t readSize=m_buffer->readBytes(m_pos, buf, size);
    m_pos+=readSize;
    
    return readSize;
}

unsigned char InputStream::readByte()
{
    return m_buffer->readByte(m_pos++);
}

uint8_t InputStream::readUInt8()
{
    return m_buffer->readUInt8(m_pos++);
}

uint16_t InputStream::readUInt16()
{
    uint16_t ret= m_endianness==kLittleEndian?m_buffer->readUInt16LE(m_pos):m_buffer->readUInt16BE(m_pos);
    m_pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

uint32_t InputStream::readUInt32()
{
    uint32_t ret= m_endianness==kLittleEndian?m_buffer->readUInt32LE(m_pos):m_buffer->readUInt32BE(m_pos);
    m_pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

uint64_t InputStream::readUInt64()
{
    uint64_t ret= m_endianness==kLittleEndian?m_buffer->readUInt64LE(m_pos):m_buffer->readUInt64BE(m_pos);
    m_pos+=_BUFFER_LONG_SIZE;
    
    return ret;
}

int8_t InputStream::readInt8()
{
    return m_buffer->readInt8(m_pos++);
}

int16_t InputStream::readInt16()
{
    int16_t ret= m_endianness==kLittleEndian?m_buffer->readInt16LE(m_pos):m_buffer->readInt16BE(m_pos);
    m_pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

int32_t InputStream::readInt32()
{
    int32_t ret= m_endianness==kLittleEndian?m_buffer->readInt32LE(m_pos):m_buffer->readInt32BE(m_pos);
    m_pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

int64_t InputStream::readInt64()
{
    int64_t ret= m_endianness==kLittleEndian?m_buffer->readInt64LE(m_pos):m_buffer->readInt64BE(m_pos);
    m_pos+=_BUFFER_LONG_SIZE;
    
    return ret;
}

float InputStream::readHalfFloat()
{
    float ret= m_endianness==kLittleEndian?m_buffer->readFloat16LE(m_pos):m_buffer->readFloat16BE(m_pos);
    m_pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

float InputStream::readFloat()
{
    float ret= m_endianness==kLittleEndian?m_buffer->readFloatLE(m_pos):m_buffer->readFloatBE(m_pos);
    m_pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

double InputStream::readDouble()
{
    float ret= m_endianness==kLittleEndian?m_buffer->readDoubleLE(m_pos):m_buffer->readDoubleBE(m_pos);
    m_pos+=_BUFFER_LONG_SIZE;
    
    return ret;
}

float InputStream::readHalfFixed()
{
    float ret= m_endianness==kLittleEndian?m_buffer->readFixed8LE(m_pos):m_buffer->readFixed8BE(m_pos);
    m_pos+=_BUFFER_SHORT_SIZE;
    
    return ret;
}

float InputStream::readFixed()
{
    float ret= m_endianness==kLittleEndian?m_buffer->readFixedLE(m_pos):m_buffer->readFixedBE(m_pos);
    m_pos+=_BUFFER_INT_SIZE;
    
    return ret;
}

void InputStream::seek(size_t lenght)
{
    m_pos+=lenght;
}

bool InputStream::eof()
{
    return m_pos >= m_buffer->getSize();
}

NS_CC_YHGE_END
