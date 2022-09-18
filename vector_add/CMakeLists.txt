
add_compile_options(
      "$<$<NOT:$<BOOL:${MSVC}>>:-Wall;-Wextra;-pedantic>"
      "$<$<BOOL:${MSVC}>:/W4;/wd4201;/wd4214;/wd4221>"
)

add_executable(vector_add_benchmark vector_add.cpp)

target_link_libraries(vector_add_benchmark
            PRIVATE
            benchmark::benchmark
            benchmark::benchmark_main)

target_compile_options(vector_add_benchmark PRIVATE "-march=native")
