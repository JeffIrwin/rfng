
#include <iostream>
#include <stdint.h>

// TODO: move to included header in a namespace

////extern void rng_fort_hello();
extern "C" void rng_fort_hello();
extern "C" int32_t get_rng_fort(int32_t const& seed);

int main()
{
    std::cout << "hello rng" << std::endl;
    rng_fort_hello();

    auto my_rand = get_rng_fort(0);

    std::cout << "my_rand = " << my_rand << std::endl;
    return 0;
}

