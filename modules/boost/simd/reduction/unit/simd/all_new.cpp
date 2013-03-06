//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 reduction toolbox - all/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of reduction components in simd mode
//////////////////////////////////////////////////////////////////////////////
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/load.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/toolbox/reduction/include/functions/all.hpp>

NT2_TEST_CASE_TPL ( all_real__1_0,  BOOST_SIMD_REAL_TYPES)
{
  using boost::simd::all;
  using boost::simd::tag::all_;
  using boost::simd::load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename boost::dispatch::meta::upgrade<T>::type   u_t;
  typedef native<T,ext_t>                        n_t;
  typedef n_t                                     vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename boost::dispatch::meta::call<all_(vT)>::type r_t;
  typedef typename boost::dispatch::meta::call<all_(T)>::type sr_t;
  typedef typename boost::dispatch::meta::scalar_of<r_t>::type ssr_t;

  // random verifications
  static const boost::simd::uint32_t NR = BOOST_SIMD_NB_RANDOM_TEST;
  {
    BOOST_SIMD_CREATE_BUF(tab_a0,T, NR, boost::simd::Valmin<T>(), boost::simd::Valmax<T>());
    double ulp0, ulpd ; ulpd=ulp0=0.0;
    for(uint32_t j = 0; j < NR/cardinal_of<n_t>::value; j++)
      {
        vT a0 = load<vT>(&tab_a0[0],j);
        r_t v = boost::simd::all(a0);
	bool z = true;
        for(int i = 0; i< cardinal_of<n_t>::value; i++)
	  {
	    z = z && (a0[j]);
	  }
	NT2_TEST_EQUAL( v, z);
        }
      }

  }
} // end of test for floating_
