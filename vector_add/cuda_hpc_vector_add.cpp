#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <execution>

const size_t size = 100'000'000;

int main([[maybe_unused]] int argc,[[maybe_unused]] char *argv[]){

    std::vector<int> A(size), B(size);

    auto assign_random = []() -> int{ return std::rand();};

    std::generate(A.begin(), A.end(), assign_random);
    std::generate(B.begin(), B.end(), assign_random);

    auto start = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::par_unseq, A.begin(), A.end(), B.begin(), A.begin(), [](const int a, const int b){
        return a + b;
    });
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "STL Transform Algorithm: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() << "ms" << std::endl;

    return 0;
}
