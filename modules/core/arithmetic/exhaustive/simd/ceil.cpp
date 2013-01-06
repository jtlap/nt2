////////////////////////////////////////////////////////////////////////
// exhaustive test in simd mode for functor nt2::ceil
//        versus nt2::standard::ceil(a0) with float elements
////////////////////////////////////////////////////////////////////////
#include <nt2/include/functions/ceil.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/iround.hpp>
#include <cmath>

#include <nt2/toolbox/standard/include/ceil.hpp>

#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/min.hpp>
#include <iostream>
typedef BOOST_SIMD_DEFAULT_EXTENSION               ext_t;
typedef boost::simd::native<float,ext_t>  n_t;
typedef typename nt2::meta::as_integer<n_t>::type   in_t;
typedef typename nt2::meta::call<nt2::tag::ceil_(n_t)>::type r_t;
typedef typename nt2::meta::call<nt2::tag::ceil_(float)>::type sr_t;
static inline sr_t repfunc(const float & a0){
  return nt2::standard::ceil(a0);
}
int main(){
  float mini = nt2::Valmin<float>();
  float maxi = nt2::Valmax<float>();
  const nt2::uint32_t N = nt2::meta::cardinal_of<n_t>::value;
  const in_t vN = nt2::splat<in_t>(N);
  const nt2::uint32_t M =  10;
  nt2::uint32_t histo[M+1];
  for(nt2::uint32_t i = 0; i < M; i++) histo[i] = 0;
  float a[N];
  a[0] = mini;
  for(nt2::uint32_t i = 1; i < N; i++)
    a[i] = nt2::successor(a[i-1], 1);
  n_t a0 = nt2::load<n_t>(&a[0],0);
  nt2::uint32_t k = 0;
  nt2::uint32_t j = 0;
  std::cout << "a line of points to wait for... be patient!" << std::endl;
  for(; a0[N-1] < maxi; a0 = nt2::successor(a0, vN))
    {
      n_t z =  nt2::ceil(a0);
      for(nt2::uint32_t i = 0; i < N; i++)
        {
           float v = repfunc(a0[i]);
           float sz = z[i];
           ++histo[nt2::min(M, nt2::iround(2*nt2::ulpdist(v, sz)))];
           ++k;
           if (k%100000000 == 0){
             std::cout << "." << std::flush; ++j;
             if (j == 80){std::cout << std::endl; j = 0;}
           }
        }
      }
    std::cout << "exhaustive test for " << std::endl;
    std::cout << " nt2::ceil versus nt2::standard::ceil(a0) " << std::endl;
    std::cout << " in simd mode and float type" << std::endl;
    for(nt2::uint32_t i = 0; i < M; i++)
      std::cout << i/2.0 << " -> " << histo[i] << std::endl;
    std::cout << k << " values computed" << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    for(nt2::uint32_t i = 0; i < M; i++)
      std::cout << i/2.0 << " -> "
                << (histo[i]*100.0/k) << "%" << std::endl;
    return 0;
}
