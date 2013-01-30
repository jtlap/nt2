//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex toolbox - csc/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of csc  components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/include/functions/csc.hpp>
#include <nt2/include/functions/csch.hpp>
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
#include <complex>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>

NT2_TEST_CASE_TPL ( csc_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::csc;
  using nt2::tag::csc_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<csc_(cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;


  // specific values tests
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(nt2::Inf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(nt2::Minf<T>())), cT(nt2::Nan<T>()), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(1, 1)),nt2::rec(nt2::sin(cT(1.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(1, 2)),nt2::rec(nt2::sin(cT(1.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(2, 1)),nt2::rec(nt2::sin(cT(2.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(2, 2)),nt2::rec(nt2::sin(cT(2.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(0, 1)),nt2::rec(nt2::sin(cT(0.0, 1.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(0, 2)),nt2::rec(nt2::sin(cT(0.0, 2.0))), 2);
  NT2_TEST_ULP_EQUAL(nt2::csc(cT(2, 0)),nt2::rec(nt2::sin(cT(2.0, 0.0))), 2);

  const int N = 20;
  cT inputs[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
      cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
      cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),nt2::Pi <T>()), cT(nt2::Inf<T>(),nt2::Pi <T>()), cT(nt2::Minf<T>(),nt2::Pi <T>()), cT(nt2::Nan<T>(),nt2::Pi <T>()),
    };

  NT2_TEST_ULP_EQUAL(nt2::csc(-inputs[0]), cT(nt2::Nan<T>(),nt2::Nan<T>()) , 3.5);
  NT2_TEST_EQUAL(nt2::csc(cT(0.0, 0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::csc(cT(-0.0, 0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::csc(cT(-0.0,-0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  NT2_TEST_EQUAL(nt2::csc(cT( 0.0,-0.0)), cT(nt2::Nan<T>(),nt2::Nan<T>()));
  for(int i=1; i < N; i++)
    {
      std::cout << "i = " << i << " -> " << inputs[i] << std::endl;
      NT2_TEST_ULP_EQUAL(nt2::csc(-inputs[i]), -nt2::csc(inputs[i]), 3.5);
      NT2_TEST_ULP_EQUAL(nt2::csc(inputs[i]), nt2::rec(nt2::sin(inputs[i])), 3);
    }
} // end of test for floating_


