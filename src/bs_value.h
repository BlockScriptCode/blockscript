#ifndef bs_value_h
#define bs_value_h

#include <stdlib.h>
#include "bs.h"


#define BS_VALUE(type, val) \
new_value((bs_value){type, {.type=(struct type){val}}})

#define IS_BOOL(val) (val.type == BS_BOOL)
#define AS_BOOL_VAL(val) (val.as.BS_BOOL)
#define AS_BOOL_CVAL(val) (val.as.BS_BOOL.value)


#define IS_INT8(val) (val.type == BS_INT8)
#define AS_INT8_VAL(val) (val.as.BS_INT8)
#define AS_INT8_CVAL(val) (val.as.BS_INT8.value)

#define IS_UINT8(val) (val.type == BS_UINT8)
#define AS_UINT8_VAL(val) (val.as.BS_UINT8)
#define AS_UINT8_CVAL(val) (val.as.BS_UINT8.value)

#define IS_INT16(val) (val.type == BS_INT16)
#define AS_INT16_VAL(val) (val.as.BS_INT16)
#define AS_INT16_CVAL(val) (val.as.BS_INT16.value)

#define IS_UINT16(val) (val.type == BS_UINT16)
#define AS_UINT16_VAL(val) (val.as.BS_UINT16)
#define AS_UINT16_CVAL(val) (val.as.BS_UINT16.value)

#define IS_INT32(val) (val.type == BS_INT32)
#define AS_INT32_VAL(val) (val.as.BS_INT32)
#define AS_INT32_CVAL(val) (val.as.BS_INT32.value)

#define IS_UINT32(val) (val.type == BS_UINT32)
#define AS_UINT32_VAL(val) (val.as.BS_UINT32)
#define AS_UINT32_CVAL(val) (val.as.BS_UINT32.value)

#define IS_INT64(val) (val.type == BS_INT64)
#define AS_INT64_VAL(val) (val.as.BS_INT64)
#define AS_INT64_CVAL(val) (val.as.BS_INT64.value)

#define IS_UINT64(val) (val.type == BS_UINT64)
#define AS_UINT64_VAL(val) (val.as.BS_UINT64)
#define AS_UINT64_CVAL(val) (val.as.BS_UINT64.value)


typedef enum {
    BS_BOOL,
    BS_INT8,
    BS_UINT8,
    BS_INT16,
    BS_UINT16,
    BS_INT32,
    BS_UINT32,
    BS_INT64,
    BS_UINT64,
    BS_STRING,
    BS_FUNCTION,
    BS_OBJECT,
} bs_value_type;


typedef struct {
    bs_value_type type;
    union {
       struct BS_BOOL           {bool value;}                BS_BOOL;
       struct BS_INT8           {int8_t value;}              BS_INT8;
       struct BS_UINT8          {uint8_t value;}             BS_UINT8;
       struct BS_INT16          {int16_t value;}             BS_INT16;
       struct BS_UINT16         {uint16_t value;}            BS_UINT16;
       struct BS_INT32          {int32_t value;}             BS_INT32;
       struct BS_UINT32         {uint32_t value;}            BS_UINT32;
       struct BS_INT64          {int64_t value;}             BS_INT64;
       struct BS_UINT64         {uint64_t value;}            BS_UINT64;
       struct BS_STRING         {char * value; int length;}  BS_STRING;
    } as;
} bs_value;


bs_value * new_value(bs_value value);
void free_value(bs_value * value);

#endif