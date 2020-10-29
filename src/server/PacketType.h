#ifndef __PACKET_TYPE_H
#define __PACKET_TYPE_H

typedef char PacketHeader_t;
#define __PACKET_HDR_SIZE               sizeof(PacketHeader_t);
#define __DECL_PACKET_HDR(name, value)  const  PacketHeader_t name = value;

__DECL_PACKET_HDR(__PCK_ACKNOWL,        0x1);   // Sent by the server
__DECL_PACKET_HDR(__PCK_CONNECT,        0x2);   // Unused?
__DECL_PACKET_HDR(__PCK_DISCONN,        0x3);   // Unused?
__DECL_PACKET_HDR(__PCK_REQUEST_COLOR,  0x4);   // Sent by client, returns:  color as unsigned int (4 bytes)
__DECL_PACKET_HDR(__PCK_SET_COLOR,      0x5);   // Sent by client, requires: color as unsigned int (4 bytes)

__DECL_PACKET_HDR(__PCK_REQUEST_MODE,   0x10);  // Sent by client, returns: current color mode as byte
__DECL_PACKET_HDR(__PCK_SET_MODE,       0x11);  // Sent by client, requires: mode to set as byte (see enum LEDMode)

#include "Color.h"
typedef struct VEC3 PCK_COLOR;

#endif