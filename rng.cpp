
#include <iostream>
#include <stdint.h>
#include <random>
#include <sstream>

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

namespace RNG
{
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
};
// TODO: add dist class for consistency with std?  I'm so tired of oop
}

void Rng::seed(int32_t const& seed_)
{
    state = seed_fort(seed_);
}

int32_t Rng::int32()
{
    return int32_fort(state);
}

int32_t remainder(int32_t i, int32_t n)
{
    return (i % n + n) % n;
}

//********

// These function signatures are based on:
//
//     https://github.com/cgsdev0/rollycubes/game/src/StringUtils.cpp

unsigned int randomChar(int k = 255) {
    std::random_device rd;
    RNG::mt19937 gen(rd());
    return remainder(gen.int32(), k + 1);
}

unsigned int srandom_char(RNG::mt19937 &gen, int k = 255) {
    //std::uniform_int_distribution<> dis(0, k);
    //return dis(gen);
    return remainder(gen.int32(), k + 1);
}

std::string generateCode(const unsigned int len, std::string seed) {
    std::seed_seq s(seed.begin(), seed.end());
    RNG::mt19937 gen(s);
    const std::string chars =
        "abcdefghjkmnpqrstuvwxyzABCDEFGHJKMNPQRSTUV23456789";
    const unsigned int l = chars.length() - 1;
    std::stringstream ss;
    for (uint i = 0; i < len; i++) {
        ss << chars[seed == "" ? randomChar(l) : srandom_char(gen, l)];
    }
    return ss.str();
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

    std::cout << "gen codes fort = " << "\n" <<
        generateCode(10, "ahhhhh") << "\n" <<
        generateCode(10, "ahhhhh") << "\n" <<
        generateCode(10, "abcdef") << "\n" <<
        generateCode(10, "")       << "\n" <<
        generateCode(10, "")       << "\n" <<
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

