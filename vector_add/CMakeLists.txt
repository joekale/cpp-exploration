
add_compile_options(
      "$<$<NOT:$<BOOL:${MSVC}>>:-Wall;-Wextra;-pedantic>"
      "$<$<BOOL:${MSVC}>:/W4;/wd4201;/wd4214;/wd4221>"
)

add_executable(simple_vector_add simple_vector_add.cpp)

# target_compile_options(simple_vector_add 
#     PRIVATE
#         "-mavx2"
# )

add_executable(transform_vector_add transform_vector_add.cpp)

add_executable(simd_vector_add simd_vector_add.cpp)
target_compile_options(simd_vector_add PRIVATE "-march=native")
