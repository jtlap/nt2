//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.exponential toolbox - expm1/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/toolbox/exponential/include/functions/expm1.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( expm1_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::expm1;
  using nt2::tag::expm1_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<expm1_(cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;
  typedef typename nt2:: meta::as_dry<T>::type dT;
  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;

  {
    typedef dT r_t;
    // specific values tests
    NT2_TEST_ULP_EQUAL(expm1(nt2::Inf<cT>()), cT(nt2::Inf<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::Minf<cT>()), cT(nt2::Mone<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::Mone<cT>()), cT(nt2::One<T>()/nt2::Exp_1<T>()-nt2::One<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::Nan<cT>()), cT(nt2::Nan<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::One<cT>()), cT(nt2::Exp_1<T>()-nt2::One<T>()), 1.0);
    NT2_TEST_ULP_EQUAL(expm1(nt2::Zero<cT>()), cT(nt2::Zero<T>()), 1.0);
  } // end of test for floating_
}
