#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <execution>

const size_t size = 100'000'000;

int main([[maybe_unused]] int argc,[[maybe_unused]] char *argv[]){

    std::vector<int> A(size), B(size);

    auto assign_random = []() -> int{ return std::rand();};

    std::generate(A.begin(), A.end(), assign_random);
    std::generate(B.begin(), B.end(), assign_random);

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

    auto start = std::chrono::high_resolution_clock::now();
    std::transform(A.begin(), A.end(), B.begin(), A.begin(), [](const int a, const int b){
        return a + b;
    });
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "R: ["; 
    for(auto av : std::views::counted(A.begin(), 10)) {
        std::cout << av << ", ";
    } 
    std::cout << "]" << std::endl;

    std::cout << "STL Transform Algorithm: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() << "ms" << std::endl;

    return 0;
}
