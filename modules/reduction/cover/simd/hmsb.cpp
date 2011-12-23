//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 reduction toolbox - hmsb/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 24/02/2011
/// 
#include <nt2/toolbox/reduction/include/functions/hmsb.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/bits.hpp>
#include <nt2/include/functions/shri.hpp>

#include <nt2/include/functions/bits.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/toolbox/constant/constant.hpp>

template < class T > 
void pb(const T & a, int N)
{
  typedef typename nt2::meta::as_integer<T>::type iT;
  iT ia =  boost::simd::bitwise_cast<iT>(a);
  //  int j = 0;
  for(int i = 0; i < N; ++i)
    {
      std::cout << (ia&1); 
      ia >>= 1; 
    }
  std::cout << std::endl; 
}

NT2_TEST_CASE_TPL ( hmsb_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Valmin<T>(), nt2::Valmax<T>());
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = nt2::hmsb(a0);
        nt2::int32_t z = 0;
        nt2::uint32_t N = cardinal_of<n_t>::value;
        std::cout << "a0 " << a0 <<  " -> ";
        pb(v, N); 
        for(nt2::uint32_t i = 0; i< N; ++i)
        {
          z |= nt2::bits(a0[i]) >> (sizeof(iT)*CHAR_BIT - 1) << i; //(N-i-1);
        }
        NT2_TEST_EQUAL( v,ssr_t(z));
        pb(z, N); 
      }
    
  }
} // end of test for floating_

NT2_TEST_CASE_TPL ( hmsb_signed_int__1_0,  NT2_SIMD_INTEGRAL_SIGNED_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Valmin<T>(), nt2::Valmax<T>());
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = nt2::hmsb(a0);
        nt2::int32_t z = 0;
        nt2::uint32_t N = cardinal_of<n_t>::value;
  std::cout << "a0 " << a0 <<  " -> ";
  pb(v, N); 
        for(nt2::uint32_t i = 0; i< N; ++i)
        {
          z |= nt2::bits(a0[i]) >> (sizeof(iT)*CHAR_BIT - 1) << i; //(N-i-1);
        }
        NT2_TEST_EQUAL( v,ssr_t(z));
        pb(z, N); 
      }
    
  }
} // end of test for signed_int_

NT2_TEST_CASE_TPL ( hmsb_unsigned_int__1_0,  NT2_SIMD_UNSIGNED_TYPES)
{
  using nt2::hmsb;
  using nt2::tag::hmsb_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<hmsb_(vT)>::type r_t;
  typedef typename nt2::meta::call<hmsb_(T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_BUF(tab_a0,T, NR, nt2::Valmin<T>(), nt2::Valmax<T>());
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = nt2::hmsb(a0);
  nt2::int32_t z = 0;
        nt2::uint32_t N = cardinal_of<n_t>::value;
  std::cout << "a0 " << a0 <<  " -> ";
  pb(v, N); 
        for(nt2::uint32_t i = 0; i< N; ++i)
        {
          z |= nt2::bits(a0[i]) >> (sizeof(iT)*CHAR_BIT - 1) << i; //(N-i-1);
        }
        NT2_TEST_EQUAL( v,ssr_t(z));
        pb(z, N); 
      }
    
  }
} // end of test for unsigned_int_
