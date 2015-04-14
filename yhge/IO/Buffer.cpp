#include "Buffer.h"
#include <string>

NS_CC_YHGE_BEGIN

Buffer::Buffer()
:_size(0)
,_data(NULL)
,_dataOwner(false)
{
    
}

Buffer::Buffer(size_t size)
:_size(size)
,_data(NULL)
,_dataOwner(true)
{
    _data=(unsigned char*) malloc( size * sizeof(unsigned char));
}

Buffer::Buffer(unsigned char* data,size_t size)
:_size(size)
,_data(data)
,_dataOwner(true)
{
    _data=(unsigned char*) malloc(size);
    memcpy(_data, data, size);
}

Buffer::Buffer(unsigned char* data,size_t size,bool dataOwner)
:_size(size)
,_data(data)
,_dataOwner(dataOwner)
{
    
}

Buffer::Buffer(unsigned char* data,size_t size,MemType type)
:_size(size)
{
    switch (type) {
        case kCopy:
            _data=(unsigned char*) malloc(size);
            memcpy(_data, data, size);
            _dataOwner=true;
            break;
        case kOwner:
            _data=data;
            _dataOwner=true;
            break;
        case kWeak:
            _data=data;
            _dataOwner=false;
            break;
        default:
            break;
    }
}

Buffer::~Buffer()
{
    if (_data && _dataOwner) {
        free(_data);
    }
}

size_t Buffer::readBytes(size_t position,void* buf,size_t size)
{
    CCAssert(position<_size,"Buffer::readBytes out index");
    
    if (position+size>_size) {
        size=_size-position;
    }
    
    memmove(buf,_data+position,size);
    
    return size;
}


//size_t Buffer::readBytesUnSafe(size_t position,void* buf,size_t size)
//{
//    CCAssert(position+size<=_size,"Buffer::readBytesSafe out index");
//    
////    if (position+size>_size) {
////        size=_size-position;
////    }
//    
//    memcpy(buf,_data+position,size);
//    
//    return size;
//}

uint64_t Buffer::readUInt64LE(size_t position)
{
    CCAssert(position+8<=_size,"Buffer::readUInt64LE out 64 index");

    unsigned char* start=_data+position;

    uint64_t val=0;

    for (int i = 0; i < 8; i++)
    {
        val |= (uint64_t)*(start+i) << (i*8);
    }

    return val;
}

uint64_t Buffer::readUInt64BE(size_t position)
{
    CCAssert(position+8<=_size,"Buffer::readUInt64BE out index");
                
    unsigned char* start=_data+position+7;

    uint64_t val=0;

    for (int i = 0; i < 8; i++)
    {
        val |= (uint64_t) *(start--) << (i*8);
    }

    return val;
}

size_t Buffer::writeBytes(size_t position,void* buf,size_t size)
{
    CCAssert(position<_size,"Buffer::writeBytes out index");
    
    if (position+size>_size) {
        size=_size-position;
    }
    
    memmove(_data+position,buf,size);
    
    return size;
}

size_t Buffer::writeBytesUnSafe(size_t position,void* buf,size_t size)
{
    CCAssert(position+size<=_size,"Buffer::writeBytes out index");
    
//    if (position+size>_size) {
//        size=_size-position;
//    }
    
    memcpy(_data+position,buf,size);
    
    return size;
}

size_t Buffer::writeUInt64LE(uint64_t value,size_t position)
{
    CCAssert(position+_BUFFER_LONG_SIZE<=_size,"Buffer::writeUInt64LE out index");
    
    
    unsigned char* start=_data+position;
    
    for (int i = 0; i < _BUFFER_LONG_SIZE; i++)
    {
        *(start+i) =  (value >> (i*8)) & 0xFF;
    }
    
    return _BUFFER_LONG_SIZE;
}

size_t Buffer::writeUInt64BE(uint64_t value,size_t position)
{
    CCAssert(position+_BUFFER_LONG_SIZE<=_size,"Buffer::writeUInt64LE out index");
    
    unsigned char* start=_data+position+7;
    
    for (int i = 0; i < _BUFFER_LONG_SIZE; i++)
    {
        *(start--) =  (value >> (i*8)) & 0xFF;
    }
    
    return _BUFFER_LONG_SIZE;
}

void Buffer::fill(unsigned char value,size_t start,size_t end)
{
    if (start<_size) {
        
        if (end>_size) {
            end=_size;
        }
        
        size_t len=end-start;
        
        if (len>0) {
            memset(_data+start, value, len);
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
    
    if (sourceStart > _size){
        CCLOG("Buffer::copy out of range index");
        return;
    }
    
    //检查目录缓存区大小是否可以容纳，不能则截取
    if (sourceEnd - sourceStart > targetLength - targetStart)
        sourceEnd = sourceStart + targetLength - targetStart;
    
    size_t to_copy = MIN(MIN(sourceEnd - sourceStart,
                               targetLength - targetStart),
                           _size - sourceStart);
    
    memmove(target->getData()+targetStart, _data+sourceStart, to_copy);
}

unsigned char* Buffer::slice(size_t start,size_t* size)
{
    CCAssert(start<_size, "Buffer::slice out of range index");
    
    if (start+(*size)>_size) {
        *size=_size-start;
    }
    
    return _data+start;
}

NS_CC_YHGE_END
