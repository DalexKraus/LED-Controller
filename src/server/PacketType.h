#ifndef __PACKET_TYPE_H
#define __PACKET_TYPE_H

#define __PCK_ACKNOWL           0x1
#define __PCK_CONNECT           0x2
#define __PCK_DISCONN           0x3
#define __PCK_REQUEST_COLOR     0x4
#define __PCK_SET_COLOR         0x5

#include "Color.h"
typedef struct VEC3 PCK_COLOR;

#endif