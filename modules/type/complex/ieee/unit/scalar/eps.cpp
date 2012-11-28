//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.ieee toolbox - eps/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <nt2/include/functions/eps.hpp>
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


NT2_TEST_CASE_TPL ( eps_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::eps;
  using nt2::tag::eps_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<eps_(cT)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;


  // specific values tests
  NT2_TEST_EQUAL(eps(nt2::Inf<cT>() ), eps(nt2::Inf<T>() ));
  NT2_TEST_EQUAL(eps(nt2::Minf<cT>()), eps(nt2::Minf<T>()));
  NT2_TEST_EQUAL(eps(nt2::Mone<cT>()), eps(nt2::Mone<T>()));
  NT2_TEST_EQUAL(eps(nt2::Nan<cT>() ), eps(nt2::Nan<T>() ));
  NT2_TEST_EQUAL(eps(nt2::One<cT>() ), eps(nt2::One<T>() ));
  NT2_TEST_EQUAL(eps(nt2::Zero<cT>()), eps(nt2::Zero<T>()));
  NT2_TEST_EQUAL(eps(cT(nt2::Inf<T>(), nt2::Inf<T>() )), eps(nt2::Inf<T>() ));
  NT2_TEST_EQUAL(eps(cT(nt2::Minf<T>(),nt2::Minf<T>())), eps(nt2::Minf<T>()));
  NT2_TEST_EQUAL(eps(cT(nt2::Mone<T>(),nt2::Mone<T>())), eps(nt2::Sqrt_2<T>()));
  NT2_TEST_EQUAL(eps(cT(nt2::Nan<T>() ,nt2::Nan<T>()) ), eps(nt2::Nan<T>() ));
  NT2_TEST_EQUAL(eps(cT(nt2::One<T>() ,nt2::One<T>()) ), eps(nt2::Sqrt_2<T>() ));
  NT2_TEST_EQUAL(eps(cT(nt2::Zero<T>(),nt2::Zero<T>())), eps(nt2::Zero<T>()));


} // end of test for floating_

