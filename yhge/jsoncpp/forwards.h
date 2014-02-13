#ifndef YHGE_JSONCPP_FORWARDS_H_
# define YHGE_JSONCPP_FORWARDS_H_

#include "YHGEMacros.h"
# include "config.h"

NS_CC_YHGE_BEGIN
	
namespace Json {

   // writer.h
   class FastWriter;
   class StyledWriter;

   // reader.h
   class Reader;

   // features.h
   class Features;

   // value.h
   typedef int Int;
   typedef unsigned int UInt;
   class StaticString;
   class Path;
   class PathArgument;
   class Value;
   class ValueIteratorBase;
   class ValueIterator;
   class ValueConstIterator;
#ifdef JSON_VALUE_USE_INTERNAL_MAP
   class ValueAllocator;
   class ValueMapAllocator;
   class ValueInternalLink;
   class ValueInternalArray;
   class ValueInternalMap;
#endif // #ifdef JSON_VALUE_USE_INTERNAL_MAP

} // namespace Json

NS_CC_YHGE_END
	
#endif // JSON_FORWARDS_H_INCLUDED
