/*******************************************************************************

Copyright (C) 2018, Ryan McClue

g_common.h
	"Common macro definitions."

GAME:
	"Cross platform 2D SDL game."

License:
	"This file is subject to the terms and conditions defined in
	'LICENSE.md', which is part of this source code package."

*******************************************************************************/

#if !defined(COMMON_H)                                                          
#define COMMON_H                                                                
                                                                                
// could turn this into a pch                                                   
                                                                                
#include <stdio.h>                                                              
#include <stdlib.h>                                                             
#include <stdint.h>                                                             
#include <stddef.h>                                                             
#include <stdbool.h>                                                            
#include <stdarg.h>                                                             
#include <string.h>                                                             
#include <errno.h>                                                              
                                                                                
#define INTERNAL static                                                         
#define PERSIST static                                                          
                                                                                
#define FALLTHROUGH_INTENDED                                                    
#define NO_DEFAULT_CASE                                                         
                                                                                
#define TO_STRING(val) #val                                                     
#define STRINGIFY(val) TO_STRING(val)                                           
                                                                                
#define COMPILER "clang-"STRINGIFY(__clang_major__)"."STRINGIFY(__clang_minor__)"."STRINGIFY(__clang_patch_level__)
                                                                                
#define PURE __attribute__((pure))                                              
#define CONST __attribute__((const)) // same as pure except no global variables 
#define HOT __attribute__((hot))                                                
#define COLD __attribute__((cold))                                              
#define CHECK __attribute__((warn_unused_result))                               
#define DEPRECATED(msg) __attribute__((deprecated(msg)))                        
#define UNUSED __attribute__((unused))                                          
#define LIKELY(val) __builtin_expect(!!(val), 1)                                
#define UNLIKELY(val) __builtin_expect(!!(val), 0)                              
#define DESIGNATED __attribute__((designated_init))                             
#define RAW_MEM __attribute__((malloc))                                         
#define NO_NULL_RET __attribute__((returns_nonnull))                            
#define NO_RETURN __attribute__((noreturn))                                     
#define PRINTF_FMT(fmt_str_index, args_index) \                                 
  __attribute__((format(printf, fmt_str_index, args_index)))                    
#define NOT_NULL _Nonnull                                                       
                                                                                
typedef unsigned int uint;                                                      
typedef uint8_t u8;                                                             
typedef uint16_t u16;
typedef uint16_t u16;                                                           
typedef uint32_t u32;                                                           
typedef uint64_t u64;                                                           
typedef int8_t int8;                                                            
typedef int16_t int16;                                                          
typedef int32_t int32;                                                          
typedef int64_t int64;                                                          
typedef char byte;                                                              
                                                                                
#define MAX(val1, val2) \                                                       
  ({ __auto_type _val1 = val1; \                                                
     __auto_type _val2 = val2; \                                                
     __builtin_types_compatible_p(_val1, _val2) ? \                             
       _val1 > _val2 ? _val1 : _val2;  : fatal(typeof(_val1), typeof(_val2)); \ 
  })                                                                            
                                                                                
#define MIN(val1, val2) \                                                       
  ({ __auto_type _val1 = val1; \                                                
     __auto_type _val2 = val2; \                                                
     (void)(&_val1 == &_val2); \                                                
     _val1 < _val2 ? _val1 : _val2; \                                           
  })                                                                            
                                                                                
RAW_MEM NO_NULL_RET void*                                                       
xmalloc(size_t const num_bytes)                                                 
{                                                                               
  void* mem = malloc(num_bytes);                                                
  if (mem == NULL) {                                                            
    fatal(                                                                      
      "Failed to allocate %zd bytes.\nErrno %d: %s",                            
      num_bytes,                                                                
      errno,                                                                    
      strerror(errno)                                                           
    );                                                                          
  } else {                                                                      
    return mem;                                                                 
  }                                                                             
}                                                                               
                                                                                
RAW_MEM NO_NULL_RET void*                                                       
xcalloc(size_t const num_items, size_t const item_size);                        
                                                                                
NO_NULL_RET void*                                                               
xrealloc(void *const restrict mem, size_t mem_change_size);                     
                                                                                
PRINTF_FMT(1, 2) NO_RETURN                                                      
fatal(char const *const restrict fmt_str, ...)                                  
{                                                                               
  PERSIST size_t const msg_str_buf_max_len = 64;                                
  char msg_str_buf[msg_str_buf_max_len];                                        
  char control_str[64] = "GCC error \"RYLANG FATAL --";                         
  va_list args;                                                                 
  va_start(args);                                                               
                                                                                
  size_t msg_str_length = vsnprintf(                                            
                            str_buf,                                            
                            str_buf_max_len - 1,                                
                            fmt_str,                                            
                            args                                                
                          );                                                    
  msg_str_buf[msg_str_len] = "\""; // is this null terminated?                  
                                                                                
  strncat(fatal_control_str, buf, max_len);                                     
                                                                                
  _Pragma(fatal_control_str);                                                   
}                                                                               
                                                                                
typedef struct {                                                                
  size_t cap;                                                                   
  size_t len;                                                                   
  size_t const elem_size;                                                       
  byte const* content;                                                          
} Buf;                                                                          
                                                                                
void*                                                                           
buf_init(size_t const elem_size)                                                
{                                                                               
                                                                                
}                                                                               
                                                                                
inline Buf*                                                                     
buf__header(void *const restrict content)                                       
{                                                                               
  return (Buf* )((byte* )content - offsetof(Buf, content));                     
}                                                                               
                                                                                
inline size_t                                                                   
buf_cap(void *const restrict content)                                           
{                                                                               
  return buf__header(content)->cap;                
	 return buf__header(content)->cap;                                             
}                                                                               
                                                                                
inline size_t                                                                   
buf_len(void *const restrict content)                                           
{                                                                               
  return buf__header(content)->len;                                             
}                                                                               
                                                                                
inline size_t                                                                   
buf_elem_size(void *const restrict content)                                     
{                                                                               
  return buf__header(content)->elem_size;                                       
}                                                                               
                                                                                
inline void                                                                     
buf_free()                                                                      
{                                                                               
  free(buf__header(content));                                                   
}                                                                               
                                                                                
#define BUF__FIT_AMOUNT(content, amount) \                                      
  amount <= BUF_CAP(content) ? 0 : content = buf__grow(content, amount, sizeof(*_content))
                                                                                
#define BUF_PUSH(content) \                                                     
  BUF__FIT_AMOUNT(content, 1), content[BUF__HEADER(content)->len++] = elem;     
                                                                                
#define BUF_FREE(content) \                                                     
  ({ __auto_type _content = content; \                                          
  content != NULL ? IS_VALID_PTR(), free(buf_header(content)) : ERROR_EXIT(msg) 
                                                                                
void*                                                                           
buf_grow(void *const content);                                                  
                                                                                
/*                                                                              
file io                                                                         
*/                                                                              
                                                                                
                                                                                
#endif            
	
	45,1          34%

                                                                                 
