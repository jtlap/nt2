//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - cnp/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of combinatorial components in scalar 
//////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/combinatorial/include/cnp.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>

NT2_TEST_CASE_TPL ( cnp_real_,  NT2_REAL_TYPES)
{
  using nt2::cnp;
  using nt2::functors::cnp_;
  typedef typename nt2::meta::call<cnp_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(  cnp(10,1), 10, 0);
  NT2_TEST_ULP_EQUAL(  cnp(10,2), 45, 0);
  NT2_TEST_ULP_EQUAL(  cnp(10,8), 45, 0);
  NT2_TEST_ULP_EQUAL(  cnp(2,1), 2, 0);
  NT2_TEST_ULP_EQUAL(  cnp(2,2), 1, 0);
  NT2_TEST_ULP_EQUAL(  cnp(nt2::Inf<T>(), nt2::Inf<T>()), nt2::Inf<T>(), 0);
  NT2_TEST_ULP_EQUAL(  cnp(nt2::Nan<T>(), nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(  cnp(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  cnp(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<T>(), 0);
} // end of test for real_

NT2_TEST_CASE_TPL ( cnp_unsigned_int_,  NT2_UNSIGNED_TYPES)
{
  using nt2::cnp;
  using nt2::functors::cnp_;
  typedef typename nt2::meta::call<cnp_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(  cnp(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  cnp(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<T>(), 0);
} // end of test for unsigned_int_

NT2_TEST_CASE_TPL ( cnp_signed_int_,  NT2_INTEGRAL_SIGNED_TYPES)
{
  using nt2::cnp;
  using nt2::functors::cnp_;
  typedef typename nt2::meta::call<cnp_(T, T)>::type r_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;

  // specific values tests
  NT2_TEST_ULP_EQUAL(  cnp(nt2::One<T>(), nt2::One<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(  cnp(nt2::Zero<T>(), nt2::Zero<T>()), nt2::One<T>(), 0);
} // end of test for signed_int_