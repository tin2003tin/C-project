#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct
{
    uint8_t r, g, b;
} Pixel;

Pixel framebuffer[WIDTH * HEIGHT];

void setPixel(int x, int y, Pixel color)
{
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        framebuffer[y * WIDTH + x] = color;
    }
}

void clearFramebuffer(Pixel color)
{
    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        framebuffer[i] = color;
    }
}

void drawLine(int x0, int y0, int x1, int y1, Pixel color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        setPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void drawRect(int x, int y, int width, int height, Pixel color)
{
    for (int i = x; i < x + width; i++)
    {
        setPixel(i, y, color);
        setPixel(i, y + height - 1, color);
    }
    for (int i = y; i < y + height; i++)
    {
        setPixel(x, i, color);
        setPixel(x + width - 1, i, color);
    }
}

void drawCircle(int x0, int y0, int radius, Pixel color)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        setPixel(x0 + x, y0 + y, color);
        setPixel(x0 + y, y0 + x, color);
        setPixel(x0 - y, y0 + x, color);
        setPixel(x0 - x, y0 + y, color);
        setPixel(x0 - x, y0 - y, color);
        setPixel(x0 - y, y0 - x, color);
        setPixel(x0 + y, y0 - x, color);
        setPixel(x0 + x, y0 - y, color);

        if (err <= 0)
        {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}

void saveFramebuffer(const char *filename)
{
    FILE *f = fopen(filename, "wb");
    if (!f)
        return;

    uint8_t fileHeader[14] = {
        'B', 'M',   // BM
        0, 0, 0, 0, // Size in bytes
        0, 0,       // Reserved
        0, 0,       // Reserved
        54, 0, 0, 0 // Start of pixel array
    };

    uint8_t infoHeader[40] = {
        40, 0, 0, 0, // Header size
        0, 0, 0, 0,  // Image width
        0, 0, 0, 0,  // Image height
        1, 0,        // Number of color planes
        24, 0,       // Bits per pixel
        0, 0, 0, 0,  // Compression
        0, 0, 0, 0,  // Image size
        0, 0, 0, 0,  // X pixels per meter
        0, 0, 0, 0,  // Y pixels per meter
        0, 0, 0, 0,  // Total colors
        0, 0, 0, 0   // Important colors
    };

    int fileSize = 54 + 3 * WIDTH * HEIGHT;
    fileHeader[2] = (uint8_t)(fileSize);
    fileHeader[3] = (uint8_t)(fileSize >> 8);
    fileHeader[4] = (uint8_t)(fileSize >> 16);
    fileHeader[5] = (uint8_t)(fileSize >> 24);

    infoHeader[4] = (uint8_t)(WIDTH);
    infoHeader[5] = (uint8_t)(WIDTH >> 8);
    infoHeader[6] = (uint8_t)(WIDTH >> 16);
    infoHeader[7] = (uint8_t)(WIDTH >> 24);

    infoHeader[8] = (uint8_t)(HEIGHT);
    infoHeader[9] = (uint8_t)(HEIGHT >> 8);
    infoHeader[10] = (uint8_t)(HEIGHT >> 16);
    infoHeader[11] = (uint8_t)(HEIGHT >> 24);

    fwrite(fileHeader, 1, 14, f);
    fwrite(infoHeader, 1, 40, f);

    for (int y = HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            Pixel p = framebuffer[y * WIDTH + x];
            uint8_t color[3] = {p.b, p.g, p.r};
            fwrite(color, 1, 3, f);
        }
    }

    fclose(f);
}

int main()
{
    Pixel white = {255, 255, 255};
    Pixel black = {0, 0, 0};
    Pixel red = {255, 0, 0};
    Pixel green = {0, 255, 0};
    Pixel blue = {0, 0, 255};

    clearFramebuffer(white);

    drawLine(100, 100, 700, 500, black);
    drawRect(200, 150, 400, 300, red);
    drawCircle(400, 300, 100, blue);

    saveFramebuffer("output.bmp");

    return 0;
}
