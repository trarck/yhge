#ifndef YHGE_IO_BUFFER_H_
#define YHGE_IO_BUFFER_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include <yhge/Base/Internals.h>
#include "IeeeHalfPrecision.h"

NS_CC_YHGE_BEGIN

#define _BUFFER_BYTE_SIZE 1
#define _BUFFER_SHORT_SIZE 2
#define _BUFFER_INT_SIZE 4
#define _BUFFER_LONG_SIZE 8


/**
 * 字节操作类
 */
class Buffer:public Ref
{
public:
    
    enum MemType{
        kCopy,
        kOwner,
        kWeak
    };
    
    Buffer();
    
    Buffer(size_t size);
    
    Buffer(unsigned char* data,size_t size);
    
    Buffer(unsigned char* data,size_t size,bool dataOwner);
    
    Buffer(unsigned char* data,size_t size,MemType type);
    
    ~Buffer();
    
    /**
     * @brief 读取一段数据
     * 是其它读取方法的基础
     *
     * @param position 要读取的偏移位置，从开头算起。
     * @param buf 读取后要放入的地方
     * @param size 要读取的数据大小
     *
     * @return 实际读取的大小。如果大小为0，则读取错误
     */
    size_t readBytes(size_t position,void* buf,size_t size);

    /**
     * @brief 不安全的读取一段数据
     * 主要是使用memcpy代替memmove
     *
     * @param position 要读取的偏移位置，从开头算起。
     * @param buf 读取后要放入的地方
     * @param size 要读取的数据大小
     *
     * @return 实际读取的大小。如果大小为0，则读取错误
     */
    inline size_t readBytesUnSafe(size_t position,void* buf,size_t size)
    {
        CCAssert(position+size<=_size,"Buffer::readBytesSafe out index");
        
        //    if (position+size>_size) {
        //        size=_size-position;
        //    }
        
        memcpy(buf,_data+position,size);
        
        return size;
    }
    
    inline unsigned char readByte(size_t position)
    {
        CCAssert(position<_size, "Buffer::readByte out index");
        return *(_data+position);
    }

    ////////////////////////////////////////////////////////////////
    // unsigned
    ////////////////////////////////////////////////////////////////
    
    /**
     * @brief 读取无符号的8位整型
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline uint8_t readUInt8(size_t position)
    {
        CCAssert(position<_size,"Buffer::readUInt8 out index");
        return *(_data+position);
    }
    
    /**
     * @brief 读取无符号的16位整型
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline uint16_t readUInt16LE(size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::readUInt16LE out index");
        return (*(_data+position+1) << 8) | *(_data+position);
    }

    /**
     * @brief 读取无符号的16位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline uint16_t readUInt16BE(size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::readUInt16BE out index");
        return (*(_data+position) << 8) | *(_data+position+1);
    }

    /**
     * @brief 读取无符号的32位整型
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline uint32_t readUInt32LE(size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::readUInt32LE out index");

        unsigned char* start=_data+position;

        uint32_t val = (uint32_t)*(start+3) << 24;
        val |= (uint32_t)*(start+2) << 16;
        val |= (uint32_t)*(start+1) << 8;
        val |= *(start);

        return val;
    }
    
    //使用字节转换来读取数据，比直接计算要慢20%左右。性能估计还是消耗在memcpy上。
    //所以还是直接使用数值运算快
    inline uint32_t readUInt32LE2(size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::readUInt32BE out index");
        
        unsigned char buf[4];
        
        readBytesUnSafe(position, buf, 4);
        
        return *((uint32_t*)buf);
    }

    /**
     * @brief 读取无符号的32位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline uint32_t readUInt32BE(size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::readUInt32BE out index");
                
        unsigned char* start=_data+position;

        uint32_t val = (uint32_t)*(start) << 24;
        val |= (uint32_t)*(start+1) << 16;
        val |= (uint32_t)*(start+2) << 8;
        val |= *(start+3);

        return val;
    }
    
    /**
     * @brief 读取无符号的64位整型
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    uint64_t readUInt64LE(size_t position);
    
    /**
     * @brief 读取无符号的64位整型
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    uint64_t readUInt64BE(size_t position);
    
    ////////////////////////////////////////////////////////////////
    // signed
    ////////////////////////////////////////////////////////////////
    
    /**
     * @brief 读取有符号的8位整型
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int8_t readInt8(size_t position)
    {
        CCAssert(position<_size,"Buffer::readInt8 out index");
        
        return (int8_t)(*(_data+position));
//        uint8_t val=readUInt8(position);
//        return (val & 0x80)?val:(0xff-val+1)*-1;
    }
    
    /**
     * @brief 读取有符号的16位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int16_t readInt16LE(size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::readInt16 out index");
        
        return (int16_t)readUInt16LE(position);
    }
    
    /**
     * @brief 读取有符号的16位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int16_t readInt16BE(size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::readInt16BE out index");
        
        return (int16_t)readUInt16BE(position);
    }
    
    /**
     * @brief 读取有符号的32位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int32_t readInt32LE(size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::readInt32 out index");
        
        return (int32_t)readUInt32LE(position);
    }
    
    /**
     * @brief 读取有符号的32位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int32_t readInt32BE(size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::readInt32 out index");
        
        return (int32_t)readUInt32BE(position);
    }
    
    /**
     * @brief 读取有符号的64位整型
     * 数据在data中使用小端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int64_t readInt64LE(size_t position)
    {
        CCAssert(position+_BUFFER_LONG_SIZE<=_size,"Buffer::readInt64 out index");
        
        return (int64_t)readUInt64LE(position);
    }
    
    /**
     * @brief 读取有符号的64位整型
     * 数据在data中使用大端保存
     * 在内存中，可以直接把无符号的数转成有符号
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline int64_t readInt64BE(size_t position)
    {
        CCAssert(position+_BUFFER_LONG_SIZE<=_size,"Buffer::readInt64 out index");
        
        return (int64_t)readUInt64BE(position);
    }

    
    ////////////////////////////////////////////////////////////////
    // float
    ////////////////////////////////////////////////////////////////
    /**
     * @brief 读取半精度的浮点数，占用2个字节
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloat16LE(size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::readFloat16LE out index");
//        uint16_t halfInt=readUInt16LE(position);
//        
//        uint32_t singleInt=0;
//        
//        //半精度转单精度
//        halfp2singlesTyped(&singleInt, &halfInt);
//        
//        return bitwise_cast<uint32_t,float>(singleInt);
        
        uint16_t halfInt=readUInt16LE(position);
        
        float val;
        
        //半精度转单精度
        halfp2singles(&val, &halfInt);
        
        return val;
    }
    
    /**
     * @brief 读取半精度的浮点数，占用2个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloat16BE(size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::readFloat16BE out index");
//        uint16_t halfInt=readUInt16BE(position);
//        
//        uint32_t singleInt=0;
//        
//        //半精度转单精度
//        halfp2singlesTyped(&singleInt, &halfInt);
//                
//        return bitwise_cast<uint32_t,float>(singleInt);
        
        uint16_t halfInt=readUInt16BE(position);
        
        float val;
        
        //半精度转单精度
        halfp2singles(&val, &halfInt);
        
        return val;
    }
    
    /**
     * @brief 读取单精度的浮点数
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloatLE(size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::readFloatLE out index");
        return byteToFloat<float,kLittleEndian>(_data+position);
    }
    
    /**
     * @brief 读取单精度的浮点数
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFloatBE(size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::readFloatBE out index");
        return byteToFloat<float,kBigEndian>(_data+position);
    }
    
    /**
     * @brief 读取双精度的浮点数
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readDoubleLE(size_t position)
    {
        CCAssert(position+8<=_size,"Buffer::readDoubleLE out index");
        return byteToFloat<double,kLittleEndian>(_data+position);
    }
    
    /**
     * @brief 读取双精度的浮点数
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readDoubleBE(size_t position)
    {
        CCAssert(position+8<=_size,"Buffer::readDoubleBE out index");
        return byteToFloat<double,kBigEndian>(_data+position);
    }
    
    ////////////////////////////////////////////////////////////////
    // fixed float 整型表示浮点数
    ////////////////////////////////////////////////////////////////
    
    /**
     * @brief 读取8位整型浮点数，占用2个字节.8.8
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixed8LE(size_t position)
    {
        return readUInt16LE(position)/0x100;
    }
    
    /**
     * @brief 读取8位整型浮点数，占用2个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixed8BE(size_t position)
    {
        return readUInt16BE(position)/0x100;
    }
    
    /**
     * @brief 读取整型浮点数，占用4个字节16.16
     * 数据在data中使用小端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixedLE(size_t position)
    {
        return readUInt32LE(position)/0x10000;
    }
    
    /**
     * @brief 读取整型浮点数，占用4个字节
     * 数据在data中使用大端保存
     *
     * @param position 要读取的偏移位置，从开头算起。
     *
     * @return 读取的值
     */
    inline float readFixedBE(size_t position)
    {
        return readUInt32BE(position)/0x10000;
    }
    
    
//    ////////////////////////////////////////////////////////////////
//    // 使用字节操作
//    ////////////////////////////////////////////////////////////////
//    inline size_t readUInt8(size_t position,uint8_t* val)
//    {
//        return readBytes(position, val, sizeof(uint8_t));
//    }
//    
//    inline size_t readUInt16LE(size_t position,uint16_t* val)
//    {
//        unsigned char buf[2];
//        
//        size_t ret=readBytes(position, buf, sizeof(uint16_t));
//        
//        if (kLittleEndian!=getEndianness()) {
//            swizzle(buf, 2);
//        }
//        
//        *val=*buf;
//        
//        return ret;
//    }
//    
//    inline size_t readUInt16BE(size_t position,uint16_t* val)
//    {
//        unsigned char buf[2];
//        
//        size_t ret=readBytes(position, buf, sizeof(uint16_t));
//        
//        if (kBigEndian!=getEndianness()) {
//            swizzle(buf, 2);
//        }
//        
//        *val=*buf;
//        
//        return ret;
//    }
    
    /**
     * @brief 写入一段数据
     * @param position 要写入的偏移位置，从开头算起。
     * @param buf 要写入的数据
     * @param size 要写入的数据大小
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeBytes(size_t position,void* buf,size_t size);
    
    /**
     * @brief 不安全写入一段数据
     * 主要使用memcpy代替memmove
     * @param position 要写入的偏移位置，从开头算起。
     * @param buf 要写入的数据
     * @param size 要写入的数据大小
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeBytesUnSafe(size_t position,void* buf,size_t size);
    
    /**
     * @brief 写入一个字节
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeByte(unsigned char value,size_t position)
    {
        CCAssert(position<_size,"Buffer::writeByte out index");
        
        *(_data+position)=value;
        
        return _BUFFER_BYTE_SIZE;
    }
    
    /**
     * @brief 写入无符号的8位整型
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt8(uint8_t value,size_t position)
    {
        CCAssert(position<_size,"Buffer::writeUInt8 out index");
        
        *(_data+position)=value;
        
        return _BUFFER_BYTE_SIZE;
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt16LE(uint16_t value,size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::writeUInt16LE out index");
        
        unsigned char* start=_data+position;
        
        *(start) = value & 0x00FF;
        *(start+1) = (value & 0xFF00) >> 8;
        
        return _BUFFER_SHORT_SIZE;
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt16BE(uint16_t value,size_t position)
    {
        CCAssert(position+_BUFFER_SHORT_SIZE<=_size,"Buffer::writeUInt16BE out index");
        
        unsigned char* start=_data+position;
        
        *(start) = (value & 0xFF00) >> 8;
        *(start+1) = value & 0x00FF;
        
        return _BUFFER_SHORT_SIZE;
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt32LE(uint32_t value,size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::writeUInt32LE out index");
        
        unsigned char* start=_data+position;
        
        *(start) = value & 0xFF;
        *(start+1) = (value >> 8 ) & 0xFF;
        *(start+2) = (value >> 16 ) & 0xFF;
        *(start+3) = (value >> 24 ) & 0xFF;
        
        return _BUFFER_INT_SIZE;
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeUInt32BE(uint32_t value,size_t position)
    {
        CCAssert(position+_BUFFER_INT_SIZE<=_size,"Buffer::writeUInt32BE out index");
        
        unsigned char* start=_data+position;
        
        *(start) = (value >> 24 ) & 0xFF;
        *(start+1) = (value >> 16 ) & 0xFF;
        *(start+2) = (value >> 8 ) & 0xFF;
        *(start+3) = value & 0xFF;
        
        return _BUFFER_INT_SIZE;
    }
    
    /**
     * @brief 写入无符号的64位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeUInt64LE(uint64_t value,size_t position);
    
    /**
     * @brief 写入无符号的64位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    size_t writeUInt64BE(uint64_t value,size_t position);
    
    /**
     * @brief 写入无符号的8位整型
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt8(int8_t value,size_t position)
    {
        return writeUInt8((uint8_t)value, position);
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt16LE(int16_t value,size_t position)
    {
        return writeUInt16LE((uint16_t)value, position);
    }
    
    /**
     * @brief 写入无符号的16位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt16BE(uint16_t value,size_t position)
    {
        return writeUInt16BE((uint16_t)value, position);
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt32LE(int32_t value,size_t position)
    {
        return writeUInt32LE((uint32_t)value, position);
    }
    
    /**
     * @brief 写入无符号的32位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt32BE(int32_t value,size_t position)
    {
        return writeUInt32BE((uint32_t)value, position);
    }
    
    /**
     * @brief 写入无符号的64位整型
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt64LE(int64_t value,size_t position)
    {
        return writeUInt64LE((uint64_t)value, position);
    }
    
    /**
     * @brief 写入无符号的64位整型
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeInt64BE(int64_t value,size_t position)
    {
        return writeUInt64BE((uint64_t)value, position);
    }
    
    /**
     * @brief 写入半精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloat16LE(float value,size_t position)
    {
        uint16_t halfInt=0;
        singles2halfp(&halfInt, &value);
        
        return writeUInt16LE(halfInt, position);
    }
    
    /**
     * @brief 写入半精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloat16BE(float value,size_t position)
    {
        uint16_t halfInt=0;
        singles2halfp(&halfInt, &value);
        
        return writeUInt16BE(halfInt, position);
    }
    
    /**
     * @brief 写入单精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloatLE(float value,size_t position)
    {
        unsigned char buf[4];
        
        floatToByte<float, kLittleEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 4);
    }
    
    /**
     * @brief 写入单精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFloatBE(float value,size_t position)
    {
        unsigned char buf[4];
        
        floatToByte<float, kBigEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 4);
    }
    
    /**
     * @brief 写入双精度浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeDoubleLE(float value,size_t position)
    {
        unsigned char buf[8];
        
        floatToByte<double, kLittleEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 8);
    }
    
    /**
     * @brief 写入双精度浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeDoubleBE(float value,size_t position)
    {
        unsigned char buf[8];
        
        floatToByte<double, kBigEndian>(value, buf);
        
        return writeBytesUnSafe(position, buf, 8);
    }
    
    /**
     * @brief 写入8.8固定浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixed8LE(float value,size_t position)
    {
        uint16_t fixedInt= (uint16_t)(value * 0x100);
        
        return writeUInt16LE(fixedInt, position);
    }
    
    /**
     * @brief 写入8.8固定浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixed8BE(float value,size_t position)
    {
        uint16_t fixedInt= (uint16_t)(value * 0x100);
        
        return writeUInt16BE(fixedInt, position);
    }
    
    /**
     * @brief 写入16.16固定浮点数
     * 使用小端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixedLE(float value,size_t position)
    {
        uint32_t fixedInt= (uint32_t)(value * 0x10000);
        
        return writeUInt32LE(fixedInt, position);
    }
    
    /**
     * @brief 写入16.16固定浮点数
     * 使用大端表示写入后的数据
     * @param value 要写入的数据
     * @param position 要写入的偏移位置，从开头算起。
     *
     * @return 实际写入的大小。如果大小为0，则写入错误
     */
    inline size_t writeFixedBE(float value,size_t position)
    {
        uint32_t fixedInt= (uint32_t)(value * 0x10000);
        
        return writeUInt32BE(fixedInt, position);
    }
    
    /**
     * @brief 用固定值填充缓冲区
     * 会写入开始位置，但不会写入结束位置
     * @param value 要填充的数据
     * @param start 开始位置，从开头算起。
     * @param end 结束的位置，从开头算起。
     */
    void fill(unsigned char value,size_t start,size_t end);
    
    inline void fill(unsigned char value,size_t start)
    {
        fill(value, start, _size);
    }
    
    inline void fill(unsigned char value)
    {
        fill(value, 0, _size);
    }
    
    /**
     * @brief 把当前缓存区的内容copy到目标缓存区
     * 包含开始位置，但不包含结束位置
     * @param target 目标缓存区
     * @param targetStart 目标缓存区开始位置
     * @param sourceStart 当前缓存区的开始位置。
     * @param sourceEnd 当前缓存区结束位置。
     */
    void copy(Buffer* target,size_t targetStart,size_t sourceStart,size_t sourceEnd);
    
    /**
     * @brief 在当前缓存区数据截取一段
     *
     * @param start 截取的开始位置。
     * @param end 截取的结束位置。
     * @param size 截取的大小。
     *
     * @return 截取段的开始指针。注意不是副本。也就是说不用删除。
     */
    unsigned char* slice(size_t start,size_t* size);
    
public:
    
    inline void setSize(size_t size)
    {
        _size = size;
    }
    
    inline size_t getSize()
    {
        return _size;
    }
    
    inline unsigned char* getData()
    {
        return _data;
    }
    
    inline void setData(unsigned char* data)
    {
        _data=data;
    }
    
    inline void setDataOwner(bool dataOwner)
    {
        _dataOwner = dataOwner;
    }
    
    inline bool isDataOwner()
    {
        return _dataOwner;
    }
    
protected:
    
    size_t _size;
    
    unsigned char* _data;
    
    bool _dataOwner;
};

NS_CC_YHGE_END

#endif // YHGE_IO_BUFFER_H_
