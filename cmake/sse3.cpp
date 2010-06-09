#include <xmmintrin.h>

int main() 
{ 
  __m128 x = _mm_hadd_ps(_mm_set1_ps(0),_mm_set1_ps(0));
  return 1; 
}
