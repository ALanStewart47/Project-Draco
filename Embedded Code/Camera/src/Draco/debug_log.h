#ifndef _DEBUG_LOG_H_
#define _DEBUG_LOG_H_

#include "sysctl.h"

#define DEBUG_LOG
#ifdef DEBUG_LOG
#define debug_log(fmt,...)  \
    do \
    { \
        printf("[%lu][%s](%04d): "fmt"\r\n",sysctl_get_time_us(),__func__,__LINE__,##__VA_ARGS__); \
    }while(0)
#else
#define debug_log(fmt,...)
#endif

//#define FACE_GET_LOG
#ifdef FACE_GET_LOG
#define face_get_log(fmt,...)  \
    do \
    { \
        printf("[%lu][%s](%04d): "fmt"\r\n",sysctl_get_time_us(),__func__,__LINE__,##__VA_ARGS__); \
    }while(0)
#else
#define face_get_log(fmt,...)
#endif

#define TRATION_LOG
#ifdef TRATION_LOG
#define tration_log(fmt,...)  \
    do \
    { \
        printf("[tration](%04d) "fmt"\r\n",__LINE__,##__VA_ARGS__); \
    }while(0)
#else
#define tration_log(fmt,...)
#endif

#endif
