//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - tchebeval/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
///
#include <nt2/toolbox/polynomials/include/functions/tchebeval.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/infinites.hpp>
#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( tchebeval_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::tchebeval;
  using nt2::tag::tchebeval_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef boost::array<T, 3 > A_t;
  typedef typename nt2::meta::call<tchebeval_(T,A_t)>::type r_t;
  typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

  static const boost::array<T, 4 > A= {{ T(1), T(2), T(3), T(4) }};

  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );

  NT2_TEST_EQUAL(tchebeval( T(1), A), T(1.5));
  NT2_TEST_EQUAL(tchebeval( T(2), A), T(8.0));
  NT2_TEST_EQUAL(tchebeval( T(3), A), T(22.5));

  // specific values tests


} // end of test for floating_


