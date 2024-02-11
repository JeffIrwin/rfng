
#include <iostream>
#include <stdint.h>

//********

// TODO: move to included header in a namespace

const int N32 = 624;
struct rng_state_t
{
    // Fortran type interface
    int32_t mt[N32];
    int32_t index_ = N32 + 1;  // wet initialization with fortran :(
};

// Fortran function interfaces
extern "C" rng_state_t seed_fort(int32_t const& seed_);
extern "C" int32_t int32_fort(rng_state_t& r);
// TODO: add uint32() which casts the fortran 64 bit result to an actual uint32

class Rng
{
    // This C++ class wraps the Fortran struct and functions
    public:
        void seed(int32_t const&);
        int32_t int32();

    private:
        rng_state_t state;
};

void Rng::seed(int32_t const& seed_)
{
    state = seed_fort(seed_);
}

int32_t Rng::int32()
{
    return int32_fort(state);
}

//********

#include <string>

int main()
{
    std::cout << "hello c++ rng" << std::endl;

    Rng rng;
    rng.seed(0);  // explicit seeding is optional
    //rng.seed(5489);  // 5489 is the default if there's no explicit seed call

    std::cout << "rngs = " <<
        rng.int32() << " " <<
        rng.int32() << " " <<
        rng.int32() << " " <<
        rng.int32() << " " <<
        rng.int32() << " " <<
        std::endl;

    //********

    // Unit test

    const std::string RED   = "\033[1;31m";
    const std::string GREEN = "\033[1;32m";
    const std::string RESET = "\033[0m";

    Rng r;
    r.seed(1);
    std::cout << "r = " <<
        r.int32() << " " <<
        r.int32() << " " <<
        r.int32() << " " <<
        std::endl;

    r.seed(0);
    if (r.int32() == -1937831252)
        std::cout << GREEN + "test passed :)" + RESET << std::endl;
    else
    {
        std::cout << RED + "test failed :(" + RESET << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

