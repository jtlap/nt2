//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/d_acos.hpp>
#include <nt2/include/functions/simd/acos.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( acos_real_1,  NT2_SIMD_REAL_TYPES)
{
  using nt2::d_acos;

  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_ULP_EQUAL(d_acos(nt2::Half<vT>()),
                     nt2::df(nt2::functor<nt2::tag::acos_>(),nt2::Half<vT>(), nt2::vand_) , 0.5);
}
