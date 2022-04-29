# Vector Processing Optimization

Note: cuda_hpc will compile without cuda but that was a test using the CUDA HPC SDK. 
```
nvc++ -O3 -stdpar -cuda -o cuda_hpc_vector_add cuda_hpc_vector_add.cppi
```
it was far slower than the others. The others came in at ~50ms building for Release.
CUDA HPC compiled with the above ran in 140ms. Current thinking is that it includes copying the vectors into GPU memory,
     but that still seems high.
