#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <stdint.h>

/**
 * Basic xorshift* implementation
 */
class Xorshift {
public:
    /**
     * Constructor seeds the generator
     * @params: seed for the generator, must be larger than zero
     */
    Xorshift(uint64_t seed) {
        _seed = seed;
    }

    /**
     * Xorshift* modified to return floats in range [-1,1]
     * @return: randomized float
     */
    float randFloat() {
        _seed ^= _seed >> 12;
        _seed ^= _seed << 25;
        _seed ^= _seed >> 27;
        return _seed * UINT64_C(2685821657736338717) / (float) 0x7FFFFFFFFFFFFFFF - 1;
    }

    /**
     * Reseed the rng
     * @params: new seed as uin64_t, >0
     */
    void reseed(uint64_t seed) {
        _seed = seed;
    }
private:
    uint64_t _seed;
};

#endif
