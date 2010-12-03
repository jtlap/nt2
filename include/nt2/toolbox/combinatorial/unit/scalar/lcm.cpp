//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - lcm/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of combinatorial components in scalar 
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/combinatorial/include/lcm.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>

NT2_TEST_CASE_TPL ( lcm_real_,  NT2_REAL_TYPES)
{
  using nt2::lcm;
  using nt2::functors::lcm_;
  typedef typename nt2::meta::call<lcm_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // specific values tests
//   NT2_TEST_ULP_EQUAL(  lcm(120,80), 240, 0);
//   NT2_TEST_ULP_EQUAL(  lcm(3,15), 15, 0);
//   NT2_TEST_ULP_EQUAL(  lcm(3,5), 15, 0);
//   NT2_TEST_ULP_EQUAL(  lcm(6,15), 30, 0);
  NT2_TEST_ULP_EQUAL(  lcm(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(  lcm(nt2::Inf<T>(),5), 5, 0);
  NT2_TEST_ULP_EQUAL(  lcm(nt2::Minf<T>(), nt2::Minf<T>()), nt2::Nan<T>(), 0);
//  NT2_TEST_ULP_EQUAL(  lcm(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  lcm(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<T>(), 0);
//  NT2_TEST_ULP_EQUAL(  lcm(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
//  NT2_TEST_ULP_EQUAL(  lcm(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
} // end of test for real_

// NT2_TEST_CASE_TPL ( lcm_unsigned_int_,  NT2_UNSIGNED_TYPES)
// {
//   using nt2::lcm;
//   using nt2::functors::lcm_;
//   typedef typename nt2::meta::call<lcm_(T, T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef T wished_r_t;

//   // specific values tests
//   NT2_TEST_ULP_EQUAL(  lcm(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
//   NT2_TEST_ULP_EQUAL(  lcm(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
// } // end of test for unsigned_int_

// NT2_TEST_CASE_TPL ( lcm_signed_int_,  NT2_INTEGRAL_SIGNED_TYPES)
// {
//   using nt2::lcm;
//   using nt2::functors::lcm_;
//   typedef typename nt2::meta::call<lcm_(T, T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef T wished_r_t;

//   // specific values tests
//   NT2_TEST_ULP_EQUAL(  lcm(nt2::Mone<T>(), nt2::Mone<T>()), nt2::One<T>(), 0);
//   NT2_TEST_ULP_EQUAL(  lcm(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
//   NT2_TEST_ULP_EQUAL(  lcm(nt2::Zero<T>(), nt2::Zero<T>()), nt2::Zero<T>(), 0);
// } // end of test for signed_int_
