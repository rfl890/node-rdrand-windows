#ifndef __RDRAND_H__
#define __RDRAND_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


int rdrand32(uint32_t *r); // returns a 32-bit random number

int rdrand64(uint64_t *r); // returns a 64-bit random number

int rdseed32(uint32_t *r); // returns a 32-bit conditioned random number, for seeding (CS)PRNGs

int rdseed64(uint64_t *r); // returns a 64-bit conditioned random number, for seeding (CS)PRNGs

int supports_rdrand(void); // returns whether the CPU supports rdrand

int rdrand_get_bytes (uint8_t *dest, unsigned int n);
int rdseed_get_bytes (uint8_t *dest, unsigned int n);

#ifdef __cplusplus
}
#endif

#endif