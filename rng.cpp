
#include <iostream>
#include <stdint.h>

//********

// TODO: move to included header in a namespace

const int N32 = 624;
struct rng // TODO: rename uppercase Rng?  C++ is fine w/ lowercase unlike Fortran clash
{
    int32_t mt[N32];
    int32_t index_ = N32 + 1;  // WET initialization with Fortran :(
};

// TODO: can this be a fn that returns rng instead of subroutine w/ out-arg?
extern "C" void seed(rng& r, int32_t const& seed_);

extern "C" int32_t get_int32(rng& r);

//********

int main()
{
    std::cout << "hello C++ rng" << std::endl;

    rng rng;
    std::cout << "rng.index_ = " << rng.index_ << std::endl;
    seed(rng, 0);
    std::cout << "rng.mt = " <<
        rng.mt[0] << " " << 
        rng.mt[1] << " " << 
        rng.mt[2] << " " << 
        rng.mt[3] << " " << 
        rng.mt[4] << " " << 
        std::endl;

    std::cout << "rngs = " <<
        get_int32(rng) << " " <<
        get_int32(rng) << " " <<
        get_int32(rng) << " " <<
        get_int32(rng) << " " <<
        get_int32(rng) << " " <<
        std::endl;

    return 0;
}

