//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/elliptic/include/functions/ellie.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL ( ellie_real,  NT2_REAL_TYPES)
{
  using nt2::ellie;
  using nt2::tag::ellie_;
  typedef typename nt2::meta::call<ellie_(T,T)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(r_t, wished_r_t);

  // specific values tests
  NT2_TEST_ULP_EQUAL(ellie(nt2::One<T>(),T(0)), nt2::One<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(ellie(nt2::Pio_2<T>(),T(0)), nt2::Pio_2<r_t>(), 0);
  NT2_TEST_ULP_EQUAL(ellie(nt2::Zero<T>(),T(0)), nt2::Zero<r_t>(), 0);
}
