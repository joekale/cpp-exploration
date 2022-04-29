#include <vector>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <execution>

const size_t size = 100'000'000;
static std::vector<int> A, B;

int main([[maybe_unused]] int argc,[[maybe_unused]] char *argv[]){

    A.resize(size);
    B.resize(size);

    auto assign_random = []([[maybe_unused]] const int val) -> int{ return std::rand();};

    std::transform(A.begin(), A.end(), A.begin(), assign_random);
    std::transform(B.begin(), B.end(), B.begin(), assign_random);

    auto start = std::chrono::high_resolution_clock::now();
    std::transform(std::execution::par_unseq, A.begin(), A.end(), B.begin(), A.begin(), [](const int a, const int b){
        return a + b;
    });
    auto end = std::chrono::high_resolution_clock::now();

    std::cout << "STL Transform Algorithm: " << std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - start).count() << "ms" << std::endl;

    return 0;
}
