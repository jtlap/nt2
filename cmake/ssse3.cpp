#include <tmmintrin.h>

int main() 
{ 
  __m128i x = _mm_abs_epi8(_mm_set1_epi8(0));
  return 1; 
}
