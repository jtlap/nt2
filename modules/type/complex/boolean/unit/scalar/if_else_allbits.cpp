//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 type.complex.boolean toolbox - if_else_allbits/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of type.complex.boolean components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/include/functions/if_else_allbits.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/constants/cnan.hpp>
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
#include <nt2/include/constants/cnan.hpp>

NT2_TEST_CASE_TPL ( if_else_allbits_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::if_else_allbits;
  using nt2::tag::if_else_allbits_;
  using nt2::logical;
  typedef std::complex<T> cT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<if_else_allbits_(cT, cT)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2:: meta::as_complex<T>::type wished_r_t;



  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;

  // specific values tests
//   NT2_TEST_EQUAL(if_else_allbits(nt2::False<cT>(), cT(1)), nt2::Cnan<cT>());
//   NT2_TEST_EQUAL(if_else_allbits(nt2::True<cT>(),cT(1)), cT(1));
  NT2_TEST_EQUAL(if_else_allbits(nt2::Inf<cT>(), cT(1)), cT(1));
  NT2_TEST_EQUAL(if_else_allbits(nt2::Minf<cT>(), cT(1)),  cT(1));
  NT2_TEST_EQUAL(if_else_allbits(nt2::Nan<cT>(), cT(1)) ,  cT(1));
  NT2_TEST_EQUAL(if_else_allbits(nt2::Zero<cT>(), cT(1)),  nt2::Cnan<cT>());
//   NT2_TEST_EQUAL(if_else_allbits(nt2::True<cT>(), cT(1)),  cT(1));
//   NT2_TEST_EQUAL(if_else_allbits(nt2::False<cT>(), cT(1)),  nt2::Cnan<cT>());


} // end of test for floating_

