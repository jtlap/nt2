//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 bitwise toolbox - shli/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/bitwise/include/shli.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>
#include <boost/simd/include/functions/twopower.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>


BOOST_SIMD_TEST_CASE_TPL ( shli_integer__2_0,  BOOST_SIMD_INTEGRAL_TYPES)
{
  
  using boost::simd::shli;
  using boost::simd::tag::shli_;
  typedef typename boost::simd::meta::as_integer<T>::type iT;
  typedef typename boost::simd::meta::call<shli_(T,iT)>::type r_t;
  typedef typename boost::simd::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test 
  BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl; 
  double ulpd;
  ulpd=0.0;


  // specific values tests
  BOOST_SIMD_TEST_EQUAL(shli(T(2),2), boost::simd::Eight<r_t>());
  BOOST_SIMD_TEST_EQUAL(shli(boost::simd::Mone<T>(),1), r_t(-2));
  BOOST_SIMD_TEST_EQUAL(shli(boost::simd::Mone<T>(),2), r_t(-4));
  BOOST_SIMD_TEST_EQUAL(shli(boost::simd::One<T>(),1), boost::simd::Two<r_t>());
  BOOST_SIMD_TEST_EQUAL(shli(boost::simd::Zero<T>(),1), boost::simd::Zero<r_t>());
} // end of test for integer_
