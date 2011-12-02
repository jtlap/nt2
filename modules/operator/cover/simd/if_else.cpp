//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 operator toolbox - if_else/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// cover test behavior of operator components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <nt2/toolbox/operator/include/functions/if_else.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/floating.hpp>
#include <nt2/sdk/meta/arithmetic.hpp>
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
#include <nt2/sdk/simd/logical.hpp>


NT2_TEST_CASE_TPL ( if_else_integer__3_0,  (boost::simd::int32_t))//NT2_SIMD_INTEGRAL_TYPES)
{
  using nt2::if_else;
  using nt2::tag::if_else_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef native<nt2::logical<T>,ext_t >        vlT;
  typedef nt2::logical<T>                         lT;
  typedef typename nt2::meta::call<if_else_(vlT,vT,vT)>::type r_t;
  typedef typename nt2::meta::call<if_else_(lT,T,T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_LOGICAL_BUF(tab_a0,T, NR);
    NT2_CREATE_BUF(tab_a1,T, NR, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
    NT2_CREATE_BUF(tab_a2,T, NR, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vlT a0 = load<vlT>(&tab_a0[0],j);
        vT a1 = load<vT>(&tab_a1[0],j);
        vT a2 = load<vT>(&tab_a2[0],j);
        r_t v = if_else(a0,a1,a2);
        std::cout << a0 << "  "<< std::endl << a1 << "  "<< std::endl << a2 << "  " << std::endl;
       for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; i++)
        {
	  //          
          std::cout << i << " -> " << a0[i] << "  " << int(a1[i]) << "  " << int(a2[i]) << "  " << std::endl; 
         NT2_TEST_EQUAL( v[i], nt2::if_else (a0[i],a1[i],a2[i]));
        }
      }
    
  }
} // end of test for integer_

NT2_TEST_CASE_TPL ( if_else_real__3_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::if_else;
  using nt2::tag::if_else_;
  using nt2::load; 
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename nt2::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef native<nt2::logical<T>,ext_t >              vlT;
  typedef nt2::logical<T>                         lT;
  typedef typename nt2::meta::call<if_else_(vlT,vT,vT)>::type r_t;
  typedef typename nt2::meta::call<if_else_(lT,T,T)>::type sr_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  double ulpd;
  ulpd=0.0;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    NT2_CREATE_LOGICAL_BUF(tab_a0,T, NR);
    NT2_CREATE_BUF(tab_a1,T, NR, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
    NT2_CREATE_BUF(tab_a2,T, NR, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<n_t>::value)
      {
        vlT a0 = load<vlT>(&tab_a0[0],j);
        vT a1 = load<vT>(&tab_a1[0],j);
        vT a2 = load<vT>(&tab_a2[0],j);
        r_t v = if_else(a0,a1,a2);
        for(nt2::uint32_t i = 0; i< cardinal_of<n_t>::value; i++)
        {
	  NT2_TEST_EQUAL( v[i],nt2::if_else (a0[i],a1[i],a2[i]));
        }
      }
    
  }
} // end of test for floating_
