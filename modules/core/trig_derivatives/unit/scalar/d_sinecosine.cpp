//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trig_derivatives/include/functions/d_sinecosine.hpp>
#include <nt2/include/functions/sinecosine.hpp>
#include <nt2/include/functions/d_sin.hpp>
#include <nt2/include/functions/d_cos.hpp>
#include <nt2/include/functions/df.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrteps.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/half.hpp>


NT2_TEST_CASE_TPL ( sincos,  NT2_REAL_TYPES)
{
  using nt2::d_sinecosine;
  T x = nt2::Half<T>();
  T dc, ds;
  d_sinecosine<nt2::medium_>(x, ds, dc);
  NT2_TEST_ULP_EQUAL(dc, nt2::d_cos(x), 0.5);
  NT2_TEST_ULP_EQUAL(ds, nt2::d_sin(x), 0.5);
}
