#ifndef T_SHA256
#define T_SHA256

#include <stdint.h>

typedef struct
{
    uint32_t state[8];  // Holds the intermediate hash state
    uint32_t count[2];  // Number of bits processed so far
    uint8_t buffer[64]; // Data block being processed
} SHA256_CTX;

void SHA256_Init(SHA256_CTX *context);
void SHA256_Update(SHA256_CTX *context, const uint8_t *data, uint32_t len);
void SHA256_Final(uint8_t digest[32], SHA256_CTX *context);

#endif