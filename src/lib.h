#ifndef __RDRAND_H__
#define __RDRAND_H__

#include <stdint.h>
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif


BOOL rdrand32(uint32_t *r); // returns a 32-bit random number

BOOL rdrand64(uint64_t *r); // returns a 64-bit random number

BOOL rdseed32(uint32_t *r); // returns a 32-bit conditioned random number, for seeding (CS)PRNGs

BOOL rdseed64(uint64_t *r); // returns a 64-bit conditioned random number, for seeding (CS)PRNGs

BOOL supports_rdrand(void); // returns whether the CPU supports rdrand

#ifdef __cplusplus
}
#endif

#endif