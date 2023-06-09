#include "lib.h"
#include <immintrin.h>
#include <intrin.h>

int rdrand32(uint32_t *r) {
    int success = 0;
    int retries = 0;
    while (
        !success
        &&
        retries < 10
    ) {
        success = _rdrand32_step(r);
        retries++;
    }
    return success;
}

int rdrand64(uint64_t *r) {
    int success = 0;
    int retries = 0;
    while (
        !success
        &&
        retries < 10
    ) {
        success = _rdrand64_step(r);
        retries++;
    }
    return success;
}

int rdseed32(uint32_t *r) {
    int success = 0;
    int retries = 0;
    while (
        !success
        &&
        retries < 10
    ) {
        success = _rdseed32_step(r);
        retries++;
    }
    return success;
}

int rdseed64(uint64_t *r) {
    int success = 0;
    int retries = 0;
    while (
        !success
        &&
        retries < 10
    ) {
        success = _rdseed64_step(r);
        retries++;
    }
    return success;
}

int rdrand_get_bytes (uint8_t *dest, unsigned int n)
{
    int remainder = n % 8;
    int blocks = (n - remainder) / 8;
    
    if (n <= 8) {
        uint64_t *random = (uint64_t *)malloc(sizeof(uint64_t));
        if (!rdrand64(random)) {
            free(random);
            return 0;
        }
        memcpy(dest, random, n);
        free(random);
        return 1;
    }
    
    if (remainder == 0) {
        uint8_t *ptr = dest;
        for (int i = 0; i < blocks; i++) {
            uint64_t *random = (uint64_t *)malloc(sizeof(uint64_t));    
            if (!rdrand64(random)) {
                free(random);
                return 0;
            }
            memcpy(ptr, random, 8);
            free(random);
            ptr += 8;
        }
        return 1;
    } else {
        // We got some extra
        uint8_t *ptr = dest;
        for (int i = 0; i < blocks; i++) {
            uint64_t *random = (uint64_t *)malloc(sizeof(uint64_t));    
            if (!rdrand64(random)) {
                free(random);
                return 0;
            }
            memcpy(ptr, random, 8);
            free(random);
            ptr += 8;
        }

        uint64_t *finalRandom = (uint64_t *)malloc(sizeof(uint64_t));    
        if (!rdrand64(finalRandom)) {
            free(finalRandom);
            return 0;
        }
        memcpy(ptr, finalRandom, remainder);
        free(finalRandom);
        return 1;
    }
    return 0;
}

int rdseed_get_bytes (uint8_t *dest, unsigned int n)
{
    int remainder = n % 8;
    int blocks = (n - remainder) / 8;
    
    if (n <= 8) {
        uint64_t *random = (uint64_t *)malloc(sizeof(uint64_t));
        if (!rdseed64(random)) {
            free(random);
            return 0;
        }
        memcpy(dest, random, n);
        free(random);
        return 1;
    }
    
    if (remainder == 0) {
        uint8_t *ptr = dest;
        for (int i = 0; i < blocks; i++) {
            uint64_t *random = (uint64_t *)malloc(sizeof(uint64_t));    
            if (!rdseed64(random)) {
                free(random);
                return 0;
            }
            memcpy(ptr, random, 8);
            free(random);
            ptr += 8;
        }
        return 1;
    } else {
        // We got some extra
        uint8_t *ptr = dest;
        for (int i = 0; i < blocks; i++) {
            uint64_t *random = (uint64_t *)malloc(sizeof(uint64_t));    
            if (!rdseed64(random)) {
                free(random);
                return 0;
            }
            memcpy(ptr, random, 8);
            free(random);
            ptr += 8;
        }

        uint64_t *finalRandom = (uint64_t *)malloc(sizeof(uint64_t));    
        if (!rdseed64(finalRandom)) {
            free(finalRandom);
            return 0;
        }
        memcpy(ptr, finalRandom, remainder);
        free(finalRandom);
        return 1;
    }
    return 0;
}


int supports_rdrand() {
    const unsigned int flag_RDRAND = (1 << 30);
    int results[4];
    __cpuid(results, 1);
    return ((results[2] & flag_RDRAND) == flag_RDRAND);
}