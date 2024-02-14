
#ifndef INCLUDE_RFNG_H
#define INCLUDE_RFNG_H

// This header includes classes rfng::mt19937 and
// rfng::uniform_int_distribution, which can act as drop-in substitutions for a
// small subset of the standard classes std::mt19937 and
// std::uniform_int_distribution.
//
// rfng::mt19937 is consistent with std::mt19937.  Given the same scalar seed,
// they will generate the same uint32's.  uniform_int_distribution is not
// consistent with std, but it should at least satisfy the conditions of being
// (1) uniformly distributed, (2) random, and (3) within the given closed
// interval.
//
// These C++ classes are just interfaces to implementations in Fortran.

#include <iostream>
#include <stdint.h>
#include <random>

namespace rfng
{

const int N32 = 624;
struct rng_state_t
{
    // Fortran type interface
    int32_t mt[N32];
    int32_t index_ = N32 + 1;  // wet initialization with fortran :(
};

// Fortran function interfaces
extern "C" rng_state_t seed_fort(const int32_t& seed_);
extern "C" rng_state_t seed_array_fort(const int32_t* seed_, const int32_t& len);
extern "C"  int32_t  int32_fort(rng_state_t& r);
extern "C" uint32_t uint32_fort(rng_state_t& r);

class mt19937
{
    public:

        mt19937()
        {
            // Default seed
        }

        mt19937(std::seed_seq& s)
        {
            // Explicit seed.  Can also pass int literals for `s`

            std::vector<std::int32_t> seeds(s.size());
            s.generate(seeds.begin(), seeds.end());
            state = seed_array_fort(&seeds[0], seeds.size());
        }

        mt19937(std::random_device::result_type r)
        {
            int32_t seed = r;
            state = seed_fort(seed);
        }

        int32_t int32()
        {
            return int32_fort(state);
        }
        uint32_t uint32()
        {
            return uint32_fort(state);
        }
        uint32_t operator()()
        {
            return uint32_fort(state);
        }

        void seed(const int32_t& s)
        {
            state = seed_fort(s);
        }

    private:
        rng_state_t state;
};

template<typename T = int32_t> class uniform_int_distribution
{
    public:
        uniform_int_distribution(T min_, T max_)
        {
            // Inclusive of both min and max
            min = min_;
            max = max_;
        }

        T operator()(mt19937& gen)
        {
            return min + remainder(gen.uint32(), max - min + 1);
        }

    private:
        T min, max;

        T remainder(T i, T n)
        {
            return (i % n + n) % n;
        }

};

}
#endif  // INCLUDE_RFNG_H

