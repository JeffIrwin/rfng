
#include <iostream>
#include <stdint.h>

//********

// TODO: move to included header in a namespace

const int N32 = 624;
struct rng // TODO: rename uppercase Rng?  c++ is fine w/ lowercase unlike fortran clash
{
    int32_t mt[N32];
    int32_t index_ = N32 + 1;  // wet initialization with fortran :(
};

//extern "C" void seed(rng& r, int32_t const& seed_);
extern "C" rng seed(int32_t const& seed_);

// TODO: add a proper oop c++ wrapper for this which is a member of a c++
// struct/class.  May need a separate struct which wraps `struct rng`, similar
// to what is happenning on fortran side
//
// Also add uint32() which casts the fortran 64 bit result to an actual
// uint32
extern "C" int32_t int32(rng& r);

//********

int main()
{
    std::cout << "hello c++ rng" << std::endl;

    auto rng = seed(0);  // explicit seeding is optional
    //auto rng = seed(5489);  // explicit seeding is optional
    //rng rng;  // default seed (5489)

    std::cout << "rngs = " <<
        int32(rng) << " " <<
        int32(rng) << " " <<
        int32(rng) << " " <<
        int32(rng) << " " <<
        int32(rng) << " " <<
        std::endl;

    return 0;
}

