#include <iostream>
#include <chrono>
#include <stdlib.h>



int main(int argc, char* argv[]) {

  
  int minN = (8*1024)/sizeof(float);  // 8kB
  int maxN = (1*1024*1024)/sizeof(float); // 1MB
  int increment = 1024/sizeof(float);

  int niter = 100000;
  
  for (int sz = minN; sz < maxN; sz+=increment) {

    float *const a_arr = (float *const) _mm_malloc(sz*sizeof(float), 64);
    float *const b_arr = (float *const) _mm_malloc(sz*sizeof(float), 64);
    
    for (int i = 0; i < sz; ++i) {
      a_arr[i] = 1.0f;
      b_arr[i] = 2.0f;
    }
    
    float ab_dot = 0.0f;
    // warmup
    for (int iter = 0; iter < 100; ++iter) {
      for (int i = 0; i < sz; ++i) {
        ab_dot += a_arr[i]*b_arr[i];
      }
    }

    auto tstart = std::chrono::high_resolution_clock::now();
    long int btick = __rdtsc(); 
    for (int iter = 0; iter < niter; ++iter) {
      #pragma unroll(16)
      for (int i = 0; i < sz; ++i) {
        ab_dot += a_arr[i]*b_arr[i];
      }
    }
    long int etick = __rdtsc(); 
    auto tend = std::chrono::high_resolution_clock::now();
    double bytes = (2.0*niter*sz*sizeof(float));
    double bperc = bytes/(etick - btick);
    std::chrono::duration<double> tdiff = tend - tstart;
    
    std::cout << 2*sz*sizeof(float) << ", " << bperc << ", " 
      << (bytes/1e9)/tdiff.count() << ", " << ab_dot << std::endl;
  }
    

}
