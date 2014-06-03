#include "Buffer.h"
#include <string>

NS_CC_YHGE_BEGIN

Buffer::Buffer()
:m_size(0)
,m_data(NULL)
,m_dataOwner(false)
{
    
}

Buffer::Buffer(size_t size)
:m_size(size)
,m_data(NULL)
,m_dataOwner(true)
{
    m_data=(unsigned char*) malloc( size * sizeof(unsigned char));
}

Buffer::Buffer(unsigned char* data,size_t size)
:m_size(size)
,m_data(data)
,m_dataOwner(true)
{
    m_data=(unsigned char*) malloc(size);
    memcpy(m_data, data, size);
}

Buffer::Buffer(unsigned char* data,size_t size,bool dataOwner)
:m_size(size)
,m_data(data)
,m_dataOwner(dataOwner)
{
    
}

Buffer::Buffer(unsigned char* data,size_t size,MemType type)
:m_size(size)
{
    switch (type) {
        case kCopy:
            m_data=(unsigned char*) malloc(size);
            memcpy(m_data, data, size);
            m_dataOwner=true;
            break;
        case kOwner:
            m_data=data;
            m_dataOwner=true;
            break;
        case kWeak:
            m_data=data;
            m_dataOwner=false;
            break;
        default:
            break;
    }
}

Buffer::~Buffer()
{
    if (m_data && m_dataOwner) {
        free(m_data);
    }
}

size_t Buffer::readBytes(size_t position,void* buf,size_t size)
{
    CCAssert(position<m_size,"Buffer::readBytes out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
    memmove(buf,m_data+position,size);
    
    return size;
}


//size_t Buffer::readBytesUnSafe(size_t position,void* buf,size_t size)
//{
//    CCAssert(position+size<=m_size,"Buffer::readBytesSafe out index");
//    
////    if (position+size>m_size) {
////        size=m_size-position;
////    }
//    
//    memcpy(buf,m_data+position,size);
//    
//    return size;
//}

uint64_t Buffer::readUInt64LE(size_t position)
{
    CCAssert(position+8<=m_size,"Buffer::readUInt64LE out 64 index");

    unsigned char* start=m_data+position;

    uint64_t val=0;

    for (int i = 0; i < 8; i++)
    {
        val |= (uint64_t)*(start+i) << (i*8);
    }

    return val;
}

uint64_t Buffer::readUInt64BE(size_t position)
{
    CCAssert(position+8<=m_size,"Buffer::readUInt64BE out index");
                
    unsigned char* start=m_data+position+7;

    uint64_t val=0;

    for (int i = 0; i < 8; i++)
    {
        val |= (uint64_t) *(start--) << (i*8);
    }

    return val;
}

size_t Buffer::writeBytes(size_t position,void* buf,size_t size)
{
    CCAssert(position<m_size,"Buffer::writeBytes out index");
    
    if (position+size>m_size) {
        size=m_size-position;
    }
    
    memmove(m_data+position,buf,size);
    
    return size;
}

size_t Buffer::writeBytesUnSafe(size_t position,void* buf,size_t size)
{
    CCAssert(position+size<=m_size,"Buffer::writeBytes out index");
    
//    if (position+size>m_size) {
//        size=m_size-position;
//    }
    
    memcpy(m_data+position,buf,size);
    
    return size;
}

size_t Buffer::writeUInt64LE(uint64_t value,size_t position)
{
    CCAssert(position+_BUFFER_LONG_SIZE<=m_size,"Buffer::writeUInt64LE out index");
    
    
    unsigned char* start=m_data+position;
    
    for (int i = 0; i < _BUFFER_LONG_SIZE; i++)
    {
        *(start+i) =  (value >> (i*8)) & 0xFF;
    }
    
    return _BUFFER_LONG_SIZE;
}

size_t Buffer::writeUInt64BE(uint64_t value,size_t position)
{
    CCAssert(position+_BUFFER_LONG_SIZE<=m_size,"Buffer::writeUInt64LE out index");
    
    unsigned char* start=m_data+position+7;
    
    for (int i = 0; i < _BUFFER_LONG_SIZE; i++)
    {
        *(start--) =  (value >> (i*8)) & 0xFF;
    }
    
    return _BUFFER_LONG_SIZE;
}

void Buffer::fill(unsigned char value,size_t start,size_t end)
{
    if (start<m_size) {
        
        if (end>m_size) {
            end=m_size;
        }
        
        size_t len=end-start;
        
        if (len>0) {
            memset(m_data+start, value, len);
        }
    }
}

void Buffer::copy(Buffer* target,size_t targetStart,size_t sourceStart,size_t sourceEnd)
{
    size_t targetLength=target->getSize();
    
    if (targetStart >= target->getSize() || sourceStart >= sourceEnd){
        //do nothing
        return;
    }
    
    if (sourceStart > m_size){
        CCLOG("Buffer::copy out of range index");
        return;
    }
    
    //检查目录缓存区大小是否可以容纳，不能则截取
    if (sourceEnd - sourceStart > targetLength - targetStart)
        sourceEnd = sourceStart + targetLength - targetStart;
    
    size_t to_copy = MIN(MIN(sourceEnd - sourceStart,
                               targetLength - targetStart),
                           m_size - sourceStart);
    
    memmove(target->getData()+targetStart, m_data+sourceStart, to_copy);
}

unsigned char* Buffer::slice(size_t start,size_t* size)
{
    CCAssert(start<m_size, "Buffer::slice out of range index");
    
    if (start+(*size)>m_size) {
        *size=m_size-start;
    }
    
    return m_data+start;
}

NS_CC_YHGE_END
