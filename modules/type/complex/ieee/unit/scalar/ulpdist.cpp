//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.ieee toolbox - ulpdist/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of ieee components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 04/12/2010
///
#include <nt2/toolbox/ieee/include/functions/ulpdist.hpp>
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


NT2_TEST_CASE_TPL ( ulpdist_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::ulpdist;
  using nt2::tag::ulpdist_;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::call<ulpdist_(cT, cT)>::type r_t;
  typedef T wished_r_t;

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
  NT2_TEST_EQUAL(ulpdist(nt2::Inf<cT>(), nt2::Inf<cT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(ulpdist(nt2::Minf<cT>(), nt2::Minf<cT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(ulpdist(nt2::Mone<cT>(), nt2::Mone<cT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(ulpdist(nt2::Nan<cT>(), nt2::Nan<cT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(ulpdist(nt2::One<cT>(), nt2::One<cT>()), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(ulpdist(nt2::Zero<cT>(), nt2::Zero<cT>()), nt2::Zero<r_t>());
} // end of test for floating_
