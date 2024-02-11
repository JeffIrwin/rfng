
#include <iostream>
#include <stdint.h>
#include <random>
//#include <sstream>

namespace RNG
{

//********

// TODO: wrap in a namespace

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
extern "C" int32_t int32_fort(rng_state_t& r);
// TODO: add uint32() which casts the fortran 64 bit result to an actual uint32

class Rng
{
    // This C++ class wraps the Fortran struct and functions
    public:
        void seed(int32_t const&);
        int32_t int32();
        //Rng mt19937();

    private:
        rng_state_t state;
};

// TODO: rename RNG namespace and/or Rng class? They can't clash.  Or just get
// rid of Rng class?
class mt19937
{
    public:

        mt19937(std::seed_seq& s)
        {
            std::vector<std::int32_t> seeds(s.size());
            s.generate(seeds.begin(), seeds.end());
            //std::cout << "C++ seeds = \n";
            //for (std::int32_t n : seeds)
            //    std::cout << n << '\n';
            ////state = seed_array_fort(s, s.size());
            state = seed_array_fort(&seeds[0], seeds.size());
        }

        mt19937(std::random_device::result_type r)
        {
            int32_t seed = r;
            //std::cout << "random_device seed = " << seed << std::endl;
            state = seed_fort(seed);
        }

        int32_t int32()
        {
            return int32_fort(state);
        }

    private:
        rng_state_t state;
// TODO: add dist class for consistency with std?  I'm so tired of oop
};

void Rng::seed(int32_t const& seed_)
{
    state = seed_fort(seed_);
}

int32_t Rng::int32()
{
    return int32_fort(state);
}

}  // namespace RNG

