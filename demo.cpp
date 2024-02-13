
#include <iostream>
#include <stdint.h>
#include <random>
#include <sstream>

#include "rfng.h"

//********

// These function signatures are based on:
//
//     https://github.com/cgsdev0/rollycubes/game/src/StringUtils.cpp

unsigned int randomChar(int k = 255) {
    std::random_device rd;
    rfng::mt19937 gen(rd());
    rfng::uniform_int_distribution<> dis(0, k);
    return dis(gen);
}

unsigned int srandom_char(rfng::mt19937 &gen, int k = 255) {
    rfng::uniform_int_distribution<> dis(0, k);
    return dis(gen);
}

std::string generateCode(const unsigned int len, std::string seed) {
    std::seed_seq s(seed.begin(), seed.end());
    rfng::mt19937 gen(s);
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

    rfng::mt19937 rng(0);  // explicit seeding is optional
    //rfng::mt19937 rng(5489);  // 5489 is the default if there's no explicit seed call
    //rfng::mt19937 rng;  // default seed

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

    rfng::mt19937 r(1);
    std::cout << "r = " <<
        r.int32() << " " <<
        r.int32() << " " <<
        r.int32() << " " <<
        std::endl;

    //std::mt19937 gen_std;
    //gen_std.seed(0);
    std::mt19937 gen_std(0);
    std::cout << "std  = " << gen_std() << std::endl;
    std::uniform_int_distribution<> dis_std(0, 255);
    std::cout << "std  = " << dis_std(gen_std) << std::endl;

    // The operator `()` of rfng::mt19937 is consistent with std's (and the
    // reference C implementation), but rfng::uniform_int_distribution is not
    // consistent with std.  I guess there's something more to it than just
    // module and add?

    //std::random_device rd;
    //rfng::mt19937 gen_rfng(rd());
    rfng::mt19937 gen_rfng(0);
    std::cout << "rfng = " << gen_rfng() << std::endl;
    rfng::uniform_int_distribution<> dis_rfng(0, 255);
    std::cout << "rfng = " << dis_rfng(gen_rfng) << std::endl;

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

