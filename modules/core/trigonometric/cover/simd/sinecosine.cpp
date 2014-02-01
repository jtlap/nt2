//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/sinecosine.hpp>
#include <boost/simd/sdk/simd/native.hpp>
extern "C" {extern long double cephes_asinl(long double);}
extern "C" {extern long double cephes_acosl(long double);}

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/pio_4.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/aligned_load.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

NT2_TEST_CASE_TPL ( sinecosine_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::sinecosine;
  using nt2::tag::sinecosine_;
  using nt2::aligned_load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::call<sinecosine_<nt2::medium_>(vT)>::type r_t;
  typedef typename nt2::meta::call<sinecosine_<nt2::medium_>(T)>::type sr_t;

  // random verifications
  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  {
    typedef typename boost::dispatch::meta::as_floating<T>::type ftype;
    NT2_CREATE_BUF(tab_a0,T, NR, T(-60), T(60));
    for(nt2::uint32_t j = 0; j < NR;j+=cardinal_of<vT>::value)
      {
        vT a0 = aligned_load<vT>(&tab_a0[0],j);
        r_t r = nt2::sinecosine<nt2::medium_>(a0);
        for(nt2::uint32_t i = 0; i< cardinal_of<vT>::value; i++)
        {

          sr_t sr =  nt2::sinecosine<nt2::medium_>(a0[i]);
          NT2_TEST_ULP_EQUAL( boost::fusion::get<0>(r)[i],
                                    boost::fusion::get<0>(sr), 1.5);
          NT2_TEST_ULP_EQUAL( boost::fusion::get<1>(r)[i],
                                    boost::fusion::get<1>(sr), 1.5);
        }
      }
  }
} // end of test for floating_
