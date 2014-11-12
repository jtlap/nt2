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

#include <nt2/arithmetic/include/functions/fma.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <vector>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/sqrtvalmax.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>

#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/dispatch/meta/as_integer.hpp>


NT2_TEST_CASE_TPL ( fma_real,  NT2_REAL_TYPES)
{

  using nt2::fma;
  using nt2::tag::fma_;
  typedef typename nt2::meta::call<fma_(T, T, T)>::type r_t;

  nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR), in3(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Mone<T>()/2, nt2::One<T>()/2);
  nt2::roll(in2, nt2::Mone<T>()/2, nt2::One<T>()/2);
  nt2::roll(in3, nt2::Mone<T>()/2, nt2::One<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i]*in2[i]+in3[i];
  }

 NT2_COVER_ULP_EQUAL(fma_, ((T, in1))((T, in2))((T, in3)), ref, 0);

}

NT2_TEST_CASE_TPL ( fma_ui, NT2_INTEGRAL_UNSIGNED_TYPES)
{

  using nt2::fma;
  using nt2::tag::fma_;
  typedef typename nt2::meta::call<fma_(T, T, T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type utype;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR), in3(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, nt2::Valmin<T>(), nt2::Valmax<T>());
  nt2::roll(in2, nt2::Valmin<T>(), nt2::Valmax<T>());
  nt2::roll(in3, nt2::Valmin<T>(), nt2::Valmax<T>());
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = T(nt2::multiplies(utype(in1[i]), utype(in2[i]))+utype(in3[i]));
  }
 NT2_COVER_ULP_EQUAL(fma_, ((T, in1))((T, in2))((T, in3)), ref, 0);

}

NT2_TEST_CASE_TPL ( fma_si, NT2_INTEGRAL_SIGNED_TYPES)
{

  using nt2::fma;
  using nt2::tag::fma_;
  typedef typename nt2::meta::call<fma_(T, T, T)>::type r_t;
  typedef typename boost::dispatch::meta::as_integer<T, unsigned>::type utype;

  static const nt2::uint32_t NR = NT2_NB_RANDOM_TEST;
  std::vector<T> in1(NR), in2(NR), in3(NR);
  std::vector<r_t> ref(NR);
  nt2::roll(in1, -nt2::Sqrtvalmax<T>()/2, nt2::Sqrtvalmax<T>()/2);
  nt2::roll(in2, -nt2::Sqrtvalmax<T>()/2, nt2::Sqrtvalmax<T>()/2);
  nt2::roll(in3, -nt2::Sqrtvalmax<T>()/2, nt2::Sqrtvalmax<T>()/2);
  for(nt2::uint32_t i=0; i < NR ; ++i)
  {
    ref[i] = in1[i]*in2[i]+in3[i];
  }
 NT2_COVER_ULP_EQUAL(fma_, ((T, in1))((T, in2))((T, in3)), ref, 0);

}


