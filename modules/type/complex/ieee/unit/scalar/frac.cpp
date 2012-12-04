//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.ieee toolbox - frac/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <nt2/toolbox/ieee/include/functions/frac.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/unary_minus.hpp>
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


NT2_TEST_CASE_TPL ( frac_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::frac;
  using nt2::tag::frac_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<frac_(cT)>::type r_t;
  typedef cT wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(frac(nt2::Inf<cT>()  ), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(frac(nt2::Minf<cT>() ), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(frac(nt2::Mone<cT>() ), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(frac(nt2::Nan<cT>()  ), nt2::Nan<r_t>());
  NT2_TEST_EQUAL(frac(nt2::One<cT>()  ), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(frac(nt2::Zero<cT>() ), nt2::Zero<r_t>());

  NT2_TEST_EQUAL(frac(cT(1.5, 2.25)), cT(0.5, 0.25));
  NT2_TEST_ULP_EQUAL(frac(cT(1.5, 2.3)), cT(0.5, 0.3), 2);
} // end of test for floating_
