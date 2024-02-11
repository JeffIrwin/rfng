
#include <iostream>
#include <stdint.h>
#include <random>
#include <sstream>

#include "rng.h"

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

    RNG::Rng rng;
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

    RNG::Rng r;
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

