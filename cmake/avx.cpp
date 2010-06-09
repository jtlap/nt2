#include <imintrin.h>

int main() 
{ 
  __m256 x = _mm256_add_ps(_mm256_set1_ps(0),_mm256_set1_ps(0));
  return 1; 
}
