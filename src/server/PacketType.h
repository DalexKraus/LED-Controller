#ifndef __PACKET_TYPE_H
#define __PACKET_TYPE_H

#define __PCK_ACKNOWL           0x1 // Sent by the server
#define __PCK_CONNECT           0x2 // Unused?
#define __PCK_DISCONN           0x3 // Unused?
#define __PCK_REQUEST_COLOR     0x4 // Sent by client, returns:  color as unsigned int (4 bytes)
#define __PCK_SET_COLOR         0x5 // Sent by client, requires: color as unsigned int (4 bytes)

#include "Color.h"
typedef struct VEC3 PCK_COLOR;

#endif