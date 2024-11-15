#pragma once
#ifndef UTILS
#define UTILS
#include <windows.h>
#include <cstddef> // For size_t
#include "Debug.h"

#ifdef __MINGW64__
#include <cstdlib>
#define BYTESWAP32(x) _byteswap_ulong(x)
#define BYTESWAP64(x) _byteswap_uint64(x)
#else
#define BYTESWAP32(x) ((x >> 24) & 0x000000FF) | ((x >> 8) & 0x0000FF00) | ((x << 8) & 0x00FF0000) | ((x << 24) & 0xFF000000)
#define BYTESWAP64(x) ((x >> 56) & 0x00000000000000FF) | ((x >> 40) & 0x000000000000FF00) | ((x >> 24) & 0x0000000000FF0000) | ((x >> 8) & 0x00000000FF000000) | ((x << 8) & 0x000000FF00000000) | ((x << 24) & 0x0000FF0000000000) | ((x << 40) & 0x00FF000000000000) | ((x << 56) & 0xFF00000000000000)
#endif


size_t b64DecodedSize(const char* in);
int b64Decode(const char* in, unsigned char* out, SIZE_T outlen);
char* b64Encode(const unsigned char* in, SIZE_T len);
size_t b64EncodedSize(size_t inlen);

VOID addInt64ToBuffer(PBYTE buffer, UINT64 value);
VOID addInt32ToBuffer(PBYTE buffer, UINT32 value);
#endif