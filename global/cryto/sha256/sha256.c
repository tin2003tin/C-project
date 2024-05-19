#include "sha256.h"
#include <string.h>
#include <stdio.h>

#define ROTATE_RIGHT(x, n) ((x >> n) | (x << (32 - n)))
#define CH(x, y, z) ((x & y) ^ (~x & z))
#define MAJ(x, y, z) ((x & y) ^ (x & z) ^ (y & z))
#define SIGMA0(x) (ROTATE_RIGHT(x, 2) ^ ROTATE_RIGHT(x, 13) ^ ROTATE_RIGHT(x, 22))
#define SIGMA1(x) (ROTATE_RIGHT(x, 6) ^ ROTATE_RIGHT(x, 11) ^ ROTATE_RIGHT(x, 25))
#define sigma0(x) (ROTATE_RIGHT(x, 7) ^ ROTATE_RIGHT(x, 18) ^ (x >> 3))
#define sigma1(x) (ROTATE_RIGHT(x, 17) ^ ROTATE_RIGHT(x, 19) ^ (x >> 10))

static const uint32_t k[64] = {0x428a2f98, 0x71374491, 0xb5c0fbcf,
                               0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98,
                               0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
                               0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
                               0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8,
                               0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85,
                               0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e,
                               0x92722c85, 0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
                               0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c,
                               0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee,
                               0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
                               0xc67178f2};
// Helper functions
static void
SHA256_Transform(SHA256_CTX *context, const uint8_t data[64]);
static void SHA256_Encode(uint8_t *output, const uint32_t *input, size_t len);
// static void SHA256_Decode(uint32_t *output, const uint8_t *input, size_t len);

void SHA256_Init(SHA256_CTX *context)
{
    context->count[0] = context->count[1] = 0;
    // Initial hash values
    context->state[0] = 0x6a09e667;
    context->state[1] = 0xbb67ae85;
    context->state[2] = 0x3c6ef372;
    context->state[3] = 0xa54ff53a;
    context->state[4] = 0x510e527f;
    context->state[5] = 0x9b05688c;
    context->state[6] = 0x1f83d9ab;
    context->state[7] = 0x5be0cd19;
}

void SHA256_Update(SHA256_CTX *context, const uint8_t *data, uint32_t len)
{
    uint32_t i, index, partLen;
    // Compute number of bytes mod 64
    index = (context->count[0] >> 3) & 0x3F;

    // Update number of bits
    if ((context->count[0] += (len << 3)) < (len << 3))
        context->count[1]++;
    context->count[1] += (len >> 29);

    partLen = 64 - index;

    // Transform as many times as possible
    if (len >= partLen)
    {
        memcpy(&context->buffer[index], data, partLen);
        SHA256_Transform(context, context->buffer);

        for (i = partLen; i + 63 < len; i += 64)
            SHA256_Transform(context, &data[i]);

        index = 0;
    }
    else
    {
        i = 0;
    }

    // Buffer remaining input
    memcpy(&context->buffer[index], &data[i], len - i);
}

void SHA256_Final(uint8_t digest[32], SHA256_CTX *context)
{
    uint8_t bits[8];
    uint32_t index, padLen;
    static const uint8_t PADDING[64] = {0x80};

    // Save number of bits
    SHA256_Encode(bits, context->count, 8);

    // Pad out to 56 mod 64.
    index = (context->count[0] >> 3) & 0x3F;
    padLen = (index < 56) ? (56 - index) : (120 - index);
    SHA256_Update(context, PADDING, padLen);

    // Append length (before padding)
    SHA256_Update(context, bits, 8);

    // Store state in digest
    SHA256_Encode(digest, context->state, 32);

    // Zeroize sensitive information.
    memset(context, 0, sizeof(*context));
}

static void SHA256_Transform(SHA256_CTX *context, const uint8_t data[64])
{
    uint32_t a, b, c, d, e, f, g, h, t1, t2, m[64];
    int i;

    // Step 1: Prepare the message schedule (W)
    for (i = 0; i < 16; ++i)
        m[i] = (data[i * 4] << 24) | (data[i * 4 + 1] << 16) | (data[i * 4 + 2] << 8) | (data[i * 4 + 3]);
    for (; i < 64; ++i)
        m[i] = sigma1(m[i - 2]) + m[i - 7] + sigma0(m[i - 15]) + m[i - 16];

    // Step 2: Initialize the working variables with the current hash value
    a = context->state[0];
    b = context->state[1];
    c = context->state[2];
    d = context->state[3];
    e = context->state[4];
    f = context->state[5];
    g = context->state[6];
    h = context->state[7];

    // Step 3: Perform the main hash computation
    for (i = 0; i < 64; ++i)
    {
        t1 = h + SIGMA1(e) + CH(e, f, g) + k[i] + m[i];
        t2 = SIGMA0(a) + MAJ(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }

    // Step 4: Add the compressed chunk to the current hash value
    context->state[0] += a;
    context->state[1] += b;
    context->state[2] += c;
    context->state[3] += d;
    context->state[4] += e;
    context->state[5] += f;
    context->state[6] += g;
    context->state[7] += h;

    // Step 5: Clear the message schedule
    memset(m, 0, sizeof(m));
}

static void SHA256_Encode(uint8_t *output, const uint32_t *input, size_t len)
{
    size_t i, j;
    for (i = 0, j = 0; j < len; i++, j += 4)
    {
        output[j] = (uint8_t)((input[i] >> 24) & 0xff);
        output[j + 1] = (uint8_t)((input[i] >> 16) & 0xff);
        output[j + 2] = (uint8_t)((input[i] >> 8) & 0xff);
        output[j + 3] = (uint8_t)(input[i] & 0xff);
    }
}

// static void SHA256_Decode(uint32_t *output, const uint8_t *input, size_t len)
// {
//     size_t i, j;
//     for (i = 0, j = 0; j < len; i++, j += 4)
//         output[i] = ((uint32_t)input[j] << 24) | ((uint32_t)input[j + 1] << 16) |
//                     ((uint32_t)input[j + 2] << 8) | ((uint32_t)input[j + 3]);
// }
