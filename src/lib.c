#include "lib.h"
#include <immintrin.h>
#include <intrin.h>

BOOL rdrand32(uint32_t *r) {
    BOOL success = FALSE;
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

BOOL rdrand64(uint64_t *r) {
    BOOL success = FALSE;
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

BOOL rdseed32(uint32_t *r) {
    BOOL success = FALSE;
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

BOOL rdseed64(uint64_t *r) {
    BOOL success = FALSE;
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

BOOL supports_rdrand() {
    const unsigned int flag_RDRAND = (1 << 30);
    int results[4];
    __cpuid(results, 1);
    return ((results[2] & flag_RDRAND) == flag_RDRAND);
}