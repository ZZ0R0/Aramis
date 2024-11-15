#include "Utils.h"

// Custom string length function
size_t CustomStrLen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void CustomStrCopy(char* dest, const char* src, size_t destSize)
{
    size_t i = 0;
    while (i + 1 < destSize && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void CustomStrCat(char* dest, const char* src, size_t destSize) {
    size_t destLen = 0;
    // Find the end of dest
    while (destLen < destSize && dest[destLen] != '\0') {
        destLen++;
    }

    size_t srcIndex = 0;
    // Append src to dest without exceeding destSize
    while (destLen + srcIndex + 1 < destSize && src[srcIndex] != '\0') {
        dest[destLen + srcIndex] = src[srcIndex];
        srcIndex++;
    }

    // Null-terminate dest
    dest[destLen + srcIndex] = '\0';
}

// Custom implementation of PathIsRelativeA
BOOL CustomPathIsRelativeA(const char* path) {
    if (path == NULL) {
        return FALSE;
    }

    // Check for drive letter (e.g., "C:\")
    if (((path[0] >= 'A' && path[0] <= 'Z') || (path[0] >= 'a' && path[0] <= 'z')) &&
        path[1] == ':' &&
        (path[2] == '\\' || path[2] == '/')) {
        return FALSE; // Absolute path
    }

    // Check for UNC path (e.g., "\\server\share")
    if ((path[0] == '\\' && path[1] == '\\') || (path[0] == '/' && path[1] == '/')) {
        return FALSE; // Absolute path
    }

    return TRUE; // Relative path
}


int b64invs[] = {62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57, 58,
                 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0, 1, 2, 3, 4, 5,
                 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27, 28,
                 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42,
                 43, 44, 45, 46, 47, 48, 49, 50, 51};

const char b64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

size_t b64EncodedSize(size_t inlen)
{
    size_t ret;

    ret = inlen;
    if (inlen % 3 != 0)
        ret += 3 - (inlen % 3);
    ret /= 3;
    ret *= 4;

    return ret;
}

char *b64Encode(const unsigned char *in, SIZE_T len)
{
    char *out;
    SIZE_T elen;
    SIZE_T i;
    SIZE_T j;
    SIZE_T v;

    if (in == NULL || len == 0)
        return NULL;

    elen = b64EncodedSize(len);
    out = (char *)LocalAlloc(LPTR, elen + 1);
    if (!out)
        return NULL;
    out[elen] = '\0';

    for (i = 0, j = 0; i < len; i += 3, j += 4)
    {
        v = in[i];
        v = i + 1 < len ? v << 8 | in[i + 1] : v << 8;
        v = i + 2 < len ? v << 8 | in[i + 2] : v << 8;

        out[j] = b64chars[(v >> 18) & 0x3F];
        out[j + 1] = b64chars[(v >> 12) & 0x3F];
        if (i + 1 < len)
        {
            out[j + 2] = b64chars[(v >> 6) & 0x3F];
        }
        else
        {
            out[j + 2] = '=';
        }
        if (i + 2 < len)
        {
            out[j + 3] = b64chars[v & 0x3F];
        }
        else
        {
            out[j + 3] = '=';
        }
    }

    return out;
}

size_t b64DecodedSize(const char *in)
{
    SIZE_T len;
    SIZE_T ret;
    SIZE_T i;

    if (in == NULL)
        return 0;

    len = strlen(in);
    ret = len / 4 * 3;

    for (i = len; i-- > 0;)
    {
        if (in[i] == '=')
        {
            ret--;
        }
        else
        {
            break;
        }
    }

    return ret;
}

int b64IsValidChar(char c)
{
    if (c >= '0' && c <= '9')
        return 1;
    if (c >= 'A' && c <= 'Z')
        return 1;
    if (c >= 'a' && c <= 'z')
        return 1;
    if (c == '+' || c == '/' || c == '=')
        return 1;
    return 0;
}

int b64Decode(const char *in, unsigned char *out, SIZE_T outlen)
{
    SIZE_T len;
    SIZE_T i;
    SIZE_T j;
    int v;

    if (in == NULL || out == NULL)
        return 0;

    len = strlen(in);
    if (outlen < b64DecodedSize(in) || len % 4 != 0)
        return 0;

    for (i = 0; i < len; i++)
    {
        if (!b64IsValidChar(in[i]))
        {
            return 0;
        }
    }

    for (i = 0, j = 0; i < len; i += 4, j += 3)
    {
        v = b64invs[in[i] - 43];
        v = (v << 6) | b64invs[in[i + 1] - 43];
        v = in[i + 2] == '=' ? v << 6 : (v << 6) | b64invs[in[i + 2] - 43];
        v = in[i + 3] == '=' ? v << 6 : (v << 6) | b64invs[in[i + 3] - 43];

        out[j] = (v >> 16) & 0xFF;
        if (in[i + 2] != '=')
            out[j + 1] = (v >> 8) & 0xFF;
        if (in[i + 3] != '=')
            out[j + 2] = v & 0xFF;
    }

    return 1;
}

VOID addInt32ToBuffer(PBYTE buffer, UINT32 value)
{
    (buffer)[0] = (value >> 24) & 0xFF;
    (buffer)[1] = (value >> 16) & 0xFF;
    (buffer)[2] = (value >> 8) & 0xFF;
    (buffer)[3] = (value) & 0xFF;
}

VOID addInt64ToBuffer(PBYTE buffer, UINT64 value)
{
    buffer[7] = value & 0xFF;
    value >>= 8;

    buffer[6] = value & 0xFF;
    value >>= 8;

    buffer[5] = value & 0xFF;
    value >>= 8;

    buffer[4] = value & 0xFF;
    value >>= 8;

    buffer[3] = value & 0xFF;
    value >>= 8;

    buffer[2] = value & 0xFF;
    value >>= 8;

    buffer[1] = value & 0xFF;
    value >>= 8;

    buffer[0] = value & 0xFF;
}
