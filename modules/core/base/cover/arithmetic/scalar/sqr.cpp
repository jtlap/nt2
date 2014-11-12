//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
//////////////////////////////////////////////////////////////////////////////
// cover test behavior of arithmetic components in scalar mode
//////////////////////////////////////////////////////////////////////////////
#include <nt2/arithmetic/include/functions/sqr.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/sqrtvalmax.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <boost/dispatch/meta/as_integer.hpp>


#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

NT2_TEST_CASE_TPL ( sqr_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::sqr;
  using nt2::tag::sqr_;
  typedef typename nt2::meta::call<sqr_(T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i]*in1[i];
  }

  NT2_COVER_ULP_EQUAL(sqr_, ((T, in1)), ref, 0);
}

NT2_TEST_CASE_TPL ( sqr_uint,  NT2_INTEGRAL_UNSIGNED_TYPES)
{

  using nt2::sqr;
  using nt2::tag::sqr_;
  typedef typename nt2::meta::call<sqr_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type utype;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  nt2::roll(in1, nt2::Valmin<T>()/2, nt2::Valmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = T(nt2::multiplies(utype(in1[i]), utype(in1[i])));
  }

  NT2_COVER_ULP_EQUAL(sqr_, ((T, in1)), ref, 0);
}
NT2_TEST_CASE_TPL ( sqr_sint,  NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::sqr;
  using nt2::tag::sqr_;
  typedef typename nt2::meta::call<sqr_(T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type utype;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR);
  nt2::roll(in1, -nt2::Sqrtvalmax<T>()/2, nt2::Sqrtvalmax<T>()/2);
  std::vector<r_t>  ref(NR);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = T(nt2::multiplies(utype(in1[i]), utype(in1[i])));
  }

  NT2_COVER_ULP_EQUAL(sqr_, ((T, in1)), ref, 0);
}

