#ifndef XORSHIFT_H
#define XORSHIFT_H

#include <stdint.h>
#include <string>
#include <cstdlib>

//Filter for random(), in this case sets the value to range [0,2]
#define FILTER (double) 0x7FFFFFFFFFFFFFFF

/**
 * Basic xorshift* implementation
 *
 * random() returns randomized doubles in range [-1,1]
 */
class Xorshift {
public:
    /**
     * Constructor seeds the generator from rand() if default seed
     * or by adding up the given string.
     * @param seed seed string
     */
    Xorshift(std::string const &seed) {

        _seed = 0;
        if (seed == "Get random map")
            _seed += rand();
        else
            for (auto i : seed)
            _seed += i;
    }

    /**
     * Xorshift*
     * @return randomized double in range [-1,1]
     */
    double random() {
        _seed ^= _seed >> 12;
        _seed ^= _seed << 25;
        _seed ^= _seed >> 27;
        //Combination of FILTER and -1 set the value to desired range
        return _seed * UINT64_C(2685821657736338717) / FILTER - 1;
    }

private:
    uint64_t _seed;
};

#endif
