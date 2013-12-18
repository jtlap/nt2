//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/elliptic/include/functions/am.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/nan.hpp>


NT2_TEST_CASE_TPL ( am_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::am;
  using nt2::tag::am_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename nt2::meta::call<am_(vT,vT, char)>::type r_t;
  typedef vT wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  T in1[] = {nt2::One<T>(),  nt2::Pio_2<T>(), nt2::Zero<T>()};
  T in1i[] =  {nt2::Inf<T>(), nt2::Minf<T>(), nt2::Nan<T>()};
  T in2[] = {nt2::One<T>(),  nt2::Half<T>(), nt2::Zero<T>() };
  char in3[] = {'a', 'k', 'm'};


 for(int i=0; i < 3 ; i++)
 {
   for(int j=0; j < 3 ; j++)
   {
     for(int k=0; k < 3 ; k++)
     {
       NT2_TEST_ULP_EQUAL(am(nt2::splat<vT>(in1[i]), nt2::splat<vT>(in2[j]), in3[k]),
                          nt2::splat<vT>(am( in1[i], in2[j], in3[k])), 1
                         );
       #ifndef BOOST_SIMD_NO_INVALIDS
       NT2_TEST_ULP_EQUAL(am(nt2::splat<vT>(in1i[i]), nt2::splat<vT>(in2[j]), in3[k]),
                          nt2::splat<vT>(am( in1i[i], in2[j], in3[k])), 1
                         );

       #endif
     }
   }
 }


}
