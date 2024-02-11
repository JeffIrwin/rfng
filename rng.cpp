
#include <iostream>
#include <stdint.h>

//********

// TODO: move to included header in a namespace
extern "C" int32_t get_rng_fort(int32_t const& seed);

//	type, bind(c) :: rng_state_t
//		integer(kind = c_int32_t) :: mt(0: n32-1)  ! state vector
//		integer(kind = c_int32_t) :: index_ = n32 + 1
//	end type rng_state_t

//#define N32 624
const int N32 = 624;
//struct struct_t
//{
//    int32_t mt[N32];
//    int32_t index_;
//};
struct rng // TODO: rename uppercase Rng?
{
    int32_t mt[N32];
    int32_t index_ = N32 + 1;  // WET initialization with Fortran :(
    //int32_t index_;
};

//extern "C" struct_t get_struct_t();
extern "C" rng get_rng();

extern "C" void seed(rng& r, int32_t const& seed_);

//********

int main()
{
    std::cout << "hello C++ rng" << std::endl;
    auto my_rand = get_rng_fort(0);
    std::cout << "my_rand = " << my_rand << std::endl;

    //auto my_struct = get_struct_t();
    //std::cout << "my_struct.index_ = " << my_struct.index_ << std::endl;
    //std::cout << "my_struct.mt = " <<
    //    my_struct.mt[0] << " " << 
    //    my_struct.mt[1] << " " << 
    //    my_struct.mt[2] << " " << 
    //    my_struct.mt[3] << " " << 
    //    my_struct.mt[4] << " " << 
    //    std::endl;

    auto my_rng = get_rng();
    std::cout << "my_rng.index_ = " << my_rng.index_ << std::endl;
    std::cout << "my_rng.mt = " <<
        my_rng.mt[0] << " " << 
        my_rng.mt[1] << " " << 
        my_rng.mt[2] << " " << 
        my_rng.mt[3] << " " << 
        my_rng.mt[4] << " " << 
        std::endl;

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

    return 0;
}

