#include <array>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ranges>
#include <immintrin.h>

const size_t size = 100'000'000;
static std::vector<int> A, B;

int main([[maybe_unused]] int argc,[[maybe_unused]] char *argv[]){

    A.resize(size);
    B.resize(size);

    auto assign_random = []([[maybe_unused]] const int val) -> int{ return std::rand();};

    std::transform(A.begin(), A.end(), A.begin(), assign_random);
    std::transform(B.begin(), B.end(), B.begin(), assign_random);

    std::cout << "A: ["; 
    for(auto av : std::views::counted(A.begin(), 10)) {
        std::cout << av << ", ";
    } 
    std::cout << "]" << std::endl;
    std::cout << "B: ["; 
    for(auto bv : std::views::counted(B.begin(), 10)) {
        std::cout << bv << ", ";
    } 
    std::cout << "]" << std::endl;

    //std::cout << "Alignment of A: " << alignof(A.data()) << " and B: " << alignof(B.data()) << "\n";

    auto start = std::chrono::high_resolution_clock::now();

    for(unsigned int i = 0; i < size; i += 4) {
        __m128i a = _mm_load_si128((__m128i *) (A.data() + i));// load A into a
        __m128i b = _mm_load_si128((__m128i *) (B.data() + i));// load B into b
        a = _mm_hadd_epi32(a, b);
        _mm_store_si128((__m128i *) (A.data() + i), a);
    }

    auto mod = size % 4;
    if (mod > 0) {
        for(unsigned int i = 1; i <= mod; i ++) {
            A[size - mod] += B[size - mod];
        }
    }
    
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "R: ["; 
    for(auto av : std::views::counted(A.begin(), 10)) {
        std::cout << av << ", ";
    } 
    std::cout << "]" << std::endl;

    std::cout << "SIMD Algorithm: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() << "ms" << std::endl;

    return 0;
}
