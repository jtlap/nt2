//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bessel toolbox - i0/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of bessel components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 16/02/2011
/// modified by jt the 17/02/2011
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/bessel/include/i0.hpp>

NT2_TEST_CASE_TPL ( i0_real__1,  (double))
{
  using nt2::i0;
  using nt2::tag::i0_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<i0_(vT)>::type r_t;
  typedef typename nt2::meta::call<i0_(T)>::type sr_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_SIMD_BUFFER(a0,T, NR, T(0), T(10));
    double ulp0 = 0.0, ulpd = 0.0;
    for(int j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<n_t>(&tab_a0[0],j);
        r_t v = i0(a0);
	std::cout << "a0 " << a0 << std::endl; 
	std::cout << "v " << v << std::endl; 
        for(int i = 0; i< cardinal_of<n_t>::value; i++) 
        {
          int k = i+j*cardinal_of<n_t>::value;
	std::cout << "tab_a0[" << k << "] " << tab_a0[k] << std::endl; 
	std::cout << "v[" << i << "] " << v[i] << std::endl; 
          NT2_TEST_ULP_EQUAL( v[i],nt2::i0(tab_a0[k]),2.5);
          ulp0 = nt2::max(ulpd,ulp0); 
        }
      }
    std::cout << "max ulp found is: " << ulp0 << std::endl; 
  }
} // end of test for real_
