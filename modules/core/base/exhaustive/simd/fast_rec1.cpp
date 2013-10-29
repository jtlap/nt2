////////////////////////////////////////////////////////////////////////
// exhaustive test in simd mode for functor nt2::fast_rec
//        versus 1.0/x with float elements
////////////////////////////////////////////////////////////////////////
#include <nt2/include/functions/fast_rec.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ilog2.hpp>
#include <nt2/include/functions/exp2.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/minf.hpp>
#include <cmath>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/aligned_load.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/sdk/error/assert_as_flexible.hpp>
#include <iostream>

namespace nt2
{
  assert_mode_t assert_mode = assert_mode_t(ASSERT_ABORT | ASSERT_LOG);
}

int main()
{
  typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;
  typedef boost::simd::native<nt2::int32_t,ext_t>   in_t;
  float mini = nt2::Valmin<float>();
  float maxi = nt2::Valmax<float>();
  const nt2::uint32_t N = nt2::meta::cardinal_of<n_t>::value;
  const in_t vN = nt2::splat<in_t>(N);
  const nt2::uint32_t M =  128;
  nt2::uint32_t histo[M+2];
  float in[M+2];
  float ref[M+2];
  float val[M+2];
  for(nt2::uint32_t i = 0; i <= M+1; i++)
  {
    histo[i] = 0;
    val[i] = nt2::Nan<float>();
    in[i] = nt2::Zero<float>();
  }

  float a[N];
  a[0] = mini;
  for(nt2::uint32_t i = 1; i < N; i++)
    a[i] = nt2::successor(a[i-1], 1);
  n_t a0 = nt2::aligned_load<n_t>(&a[0],0);
  nt2::uint32_t k = 0, j = 0;
  for(; a0[N-1] < maxi; a0 = nt2::successor(a0, vN))
    {
      n_t z =  nt2::fast_rec(a0);
      for(nt2::uint32_t i = 0; i < N; i++)
        {
           float v = 1./(a0[i]);
           float sz = z[i];
           double u = nt2::ulpdist(v, sz)*2.0+1.0;
           if(nt2::is_invalid(u))
           {
              ++histo[M+1];
              if (abs(in[M+1]) >= abs(a0[i]))
              {
                in [M+1] = a0[i];
                ref[M+1] = v;
                val[M+1] = z[i];
              }
           }
           else
           {
             int p = nt2::min(int(M), int(nt2::ilog2(nt2::iround(u))));
             if (abs(in[i]) >= abs(a0[i]))
             {
               in[p] = a0[i];
               ref[p] = v;
               val[p] = z[i];
             }
             ++histo[p];
           }

           ++k;
           if (k%100000000 == 0)
             {
               std::cout << "." << std::flush;
               ++j;
               if (j == 80)
                 {
                   std::cout << std::endl;
                   j = 0;
                 }
             }
        }
      }
  std::cout << "exhaustive test for " << std::endl;
  std::cout << " nt2::fast_rec(x) versus 1.0/x " << std::endl;
  std::cout << " in simd mode and float type" << std::endl;
  std::cout << std::endl;
  double d = 1;
  for( nt2::uint32_t i = 0; i <= M; i++, d*= 2.0)
  {

    if( histo[i])
    {
      std::cout << (d < 2 ? 0 : d/4) << " -> "
                << histo[i]
                << " at x = " << in[i]
                << " ref = " << ref[i]
                << " and val = " << val[i]
                << std::endl;
    }
  }

  if( histo[M+1])
    std::cout << "Nan"<< " -> " << histo[M+1]
              << " at x = " << in[M+1]
              << " ref = " << ref[M+1]
              << " and val = " << val[M+1]
              << std::endl;
  std::cout << k << " values computed" << std::endl;
  std::cout << std::endl;
  std::cout << std::endl;
  d = 1;
  for( nt2::uint32_t i = 0; i <= M; i++, d*= 2.0)
  {
    if( histo[i])
    {
      std::cout << (d < 2 ? 0 : d/4) << " -> "
                << (histo[i]*100.0/k) << "%" << std::endl;
    }
  }
  if( histo[M+1])
    std::cout << "Nan"<< " -> " << (histo[M+1]*100.0/k)<< "%"  << std::endl;
  return 0;
}
