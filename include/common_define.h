#ifndef _DL_COMMON_H
#define _DL_COMMON_H

#include <server_define.h>
#include <hiredis.h>

/*************************************************************************************
 * Struct Defines.....
 *************************************************************************************/

typedef struct
{
    int             count;

    struct _conn
    {
        char            host[16];
        int             port;
        redisContext*   c;
    } conn[MAX_REDIS_COUNT];
} REDIS;


#define MAX_REDIS_KEY_COUNT         8
typedef struct
{
    int             count;
    char            key[32][MAX_REDIS_KEY_COUNT];
} REDIS_KEYS;

/*************************************************************************************
 * Error Defines.....
 *************************************************************************************/

#define SRERR_SUCCESS               0

#define SRERR_UNDEFINED_TRID        1
#define SRERR_NOTFOUND_KEY          2
#define SRERR_INCORRECT_KEYCOUNT    3

#define SRERR_SYSTEM_ERROR          9999


#endif
