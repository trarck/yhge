#ifndef YHGE_IO_INPUTSTREAM_H_
#define YHGE_IO_INPUTSTREAM_H_

#include "Buffer.h"

NS_CC_YHGE_BEGIN

/**
 * 字节流操作类
 * 这里使用和Buffer的组合，而没有使用继承，添加灵活性
 */
class InputStream:public Ref
{
public:
    
    InputStream();
    
    bool init();
    
    bool init(Buffer* buffer);
    
    bool initWithStream(InputStream* stream);
    
    ~InputStream();
    
    size_t readBytes(void* buf,size_t size);
    
    unsigned char readByte();
    
    uint8_t readUInt8();
    
    uint16_t readUInt16();
    
    uint32_t readUInt32();
    
    uint64_t readUInt64();
    
    int8_t readInt8();
    
    int16_t readInt16();
    
    int32_t readInt32();
    
    int64_t readInt64();
    
    float readHalfFloat();
    
    float readFloat();
    
    double readDouble();
    
    float readHalfFixed();
    
    float readFixed();
    
    void seek(size_t lenght);

    bool eof();
    
public:
    
    inline void setBuffer(Buffer* buffer)
    {
        CC_SAFE_RETAIN(buffer);
        CC_SAFE_RELEASE(m_buffer);
        m_buffer = buffer;
    }
    
    inline Buffer* getBuffer()
    {
        return m_buffer;
    }
    
    inline void setPos(size_t pos)
    {
        m_pos = pos;
    }
    
    inline size_t getPos()
    {
        return m_pos;
    }
    
    inline void setEndianness(Endianness endianness)
    {
        m_endianness = endianness;
    }
    
    inline Endianness getEndianness()
    {
        return m_endianness;
    }
    
protected:
    
    Buffer* m_buffer;
    
    size_t m_pos;
    
    //字节流使用的顺序
    Endianness m_endianness;
    
};

NS_CC_YHGE_END

#endif // YHGE_IO_INPUTSTREAM_H_
