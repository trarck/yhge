#ifndef YHGE_IO_OutputStream_H_
#define YHGE_IO_OutputStream_H_

#include "Buffer.h"

NS_CC_YHGE_BEGIN

/**
 * 字节流操作类
 * 这里使用和Buffer的组合，而没有使用继承，添加灵活性
 */
class OutputStream:public Ref
{
public:
    
    OutputStream();
    
    ~OutputStream();

    bool init();
    
    bool init(Buffer* buffer);
    
    bool initWithStream(OutputStream* stream);
    
    void writeBytes(void* buf,size_t size);
    
    void writeByte(unsigned char value);
    
    void writeUInt8(uint8_t value);
    
    void writeUInt16(uint16_t value);
    
    void writeUInt32(uint32_t value);
    
    void writeUInt64(uint64_t value);
    
    void writeInt8(int8_t value);
    
    void writeInt16(int16_t value);
    
    void writeInt32(int32_t value);
    
    void writeInt64(int64_t value);
    
    void writeHalfFloat(float value);
    
    void writeFloat(float value);
    
    void writeDouble(double value);
    
    void writeHalfFixed(float value);
    
    void writeFixed(float value);

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
    
    void seek(size_t lenght);
    
    bool eof();
    
protected:
    
    Buffer* m_buffer;
    
    size_t m_pos;
    
    //字节流使用的顺序
    Endianness m_endianness;
};

NS_CC_YHGE_END

#endif // YHGE_IO_OutputStream_H_
