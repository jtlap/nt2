#include <smmintrin.h>
#include <ammintrin.h>

int main() 
{ 
  __m128d x = _mm_blend_pd(_mm_set1_pd(0),_mm_set1_pd(0));
  return 1; 
}
