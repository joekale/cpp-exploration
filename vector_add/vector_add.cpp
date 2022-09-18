#include <benchmark/benchmark.h>

#include <immintrin.h>
#include <execution>


const size_t size = 100'000'000;
std::vector<int> A(size), B(size);

static void DoSetup(const benchmark::State& state) {
    auto assign_random = []() -> int{ return std::rand();};

    std::generate(A.begin(), A.end(), assign_random);
    std::generate(B.begin(), B.end(), assign_random);
}

static void BM_SimpleVectorAdd(benchmark::State& state) {
  for (auto _ : state) {
    for(unsigned int i = 0; i < size; i++) {
        A[i] += B[i];
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SimpleVectorAdd)->Setup(DoSetup);

static void BM_StdTransformVectorAdd(benchmark::State& state) {
  for (auto _ : state) {
    std::transform(std::execution::par_unseq, A.begin(), A.end(), B.begin(), A.begin(), [](const int a, const int b){
        return a + b;
    });
  }
}
// Register the function as a benchmark
BENCHMARK(BM_StdTransformVectorAdd)->Setup(DoSetup);

static void BM_StdTransformParVectorAdd(benchmark::State& state) {
  for (auto _ : state) {
    std::transform(A.begin(), A.end(), B.begin(), A.begin(), [](const int a, const int b){
        return a + b;
    });
  }
}
// Register the function as a benchmark
BENCHMARK(BM_StdTransformParVectorAdd)->Setup(DoSetup);

static void BM_SIMDVectorAdd(benchmark::State& state) {
  for (auto _ : state) {
    for(unsigned int i = 0; i < size; i += 4) {
        __m128i a = _mm_load_si128((__m128i *) (A.data() + i));// load A into a
        __m128i b = _mm_load_si128((__m128i *) (B.data() + i));// load B into b
        a = _mm_add_epi32(a, b);
        _mm_store_si128((__m128i *) (A.data() + i), a);
    }

    auto mod = size % 4;
    if (mod > 0) {
        for(unsigned int i = 1; i <= mod; i ++) {
            A[size - mod] += B[size - mod];
        }
    }
  }
}
// Register the function as a benchmark
BENCHMARK(BM_SIMDVectorAdd)->Setup(DoSetup);

BENCHMARK_MAIN();