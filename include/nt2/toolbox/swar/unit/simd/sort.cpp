//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 swar toolbox - sort/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// modified by jt the 20/03/2011
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
#include <nt2/include/functions/max.hpp>
#include <nt2/toolbox/swar/include/sort.hpp>

NT2_TEST_CASE_TPL ( sort_gt_16__1_0,  (int32_t)(uint32_t)(int64_t)(uint64_t)(float)(double))
{
  using nt2::sort;
  using nt2::tag::sort_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<sort_(vT)>::type r_t;
  typedef typename nt2::meta::call<sort_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;

  // random verifications
  static const uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, 0, 100);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = sort(a0);
        T z[cardinal_of<r_t>::value];
        for(uint32_t i=0; i<cardinal_of<n_t>::value; i++) z[i]=a0[i];
        for(uint32_t i=0; i<cardinal_of<n_t>::value; i++){
          for(uint32_t k=0; k<cardinal_of<n_t>::value; k++){
             if (z[i]<z[k]) std::swap(z[i],z[k]);
          }
        }
        for(uint32_t i=0; i<cardinal_of<n_t>::value; i++){
          NT2_TEST_EQUAL(v[i],z[i]);
        }
      }
    
  }
} // end of test for gt_16_
