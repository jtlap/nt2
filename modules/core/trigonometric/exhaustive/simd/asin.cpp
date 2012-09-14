//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// exhaustive cover behavior for float values
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/trigonometric/include/asin.hpp>
#include <nt2/toolbox/ieee/include/successor.hpp>
#include <nt2/toolbox/ieee/include/ulpdist.hpp>
#include <nt2/toolbox/operator/include/splat.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/toolbox/crlibm/include/asin_rn.hpp>
#include <nt2/include/functions/min.hpp>
#include <iostream>

int main(){
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef boost::simd::native<float,ext_t>           n_t;
  typedef boost::simd::native<nt2::int32_t,ext_t>  in_t;
  float mini = nt2::Mone<float>();
  float maxi = nt2::One<float>();
  const nt2::uint32_t N = nt2::meta::cardinal_of<n_t>::value;
  const in_t vN = nt2::splat<in_t>(N); 
  const nt2::uint32_t M =  10; 
  nt2::uint32_t histo[M+1];
  for(nt2::uint32_t i = 0; i < M; i++) histo[i] = 0; 
  float a[N];
  a[0] = mini;
  for(nt2::uint32_t i = 1; i < N; i++) a[i] = nt2::successor(a[i-1], 1);
  n_t a0 = nt2::load<n_t>(&a[0],0);
  int k = 0; 
  for(; a0[N-1] < maxi; a0 = nt2::successor(a0, vN))
    {
      n_t z =  nt2::asin(a0);
      for(nt2::uint32_t i = 0; i < N; i++)
	{
	  float v = nt2::crlibm::asin_rn(a0[i]);
	  float sz = z[i]; 
	  ++histo[nt2::min(M, nt2::iround(2*nt2::ulpdist(v, sz)))];
	  ++k; 
	}
    }
  for(nt2::uint32_t i = 0; i < M; i++)
    std::cout << i/2.0 << " -> " << histo[i] << std::endl;
  return 0; 
}
