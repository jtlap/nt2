//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define BOOST_SIMD_UNIT_MODULE "nt2 operator toolbox - splat/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of operator components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
/// 
#include <boost/simd/toolbox/operator/include/splat.hpp>
#include <boost/simd/include/functions/ulpdist.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/simd/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/unit/tests.hpp>
#include <boost/simd/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <boost/simd/include/constants/real.hpp>
#include <boost/simd/include/constants/infinites.hpp>

//COMMENTED
BOOST_SIMD_TEST_CASE_TPL ( splat_integer__1_0,  BOOST_SIMD_INTEGRAL_TYPES)
{
  
//   using boost::simd::splat;
//   using boost::simd::tag::splat_;
//   typedef typename boost::simd::meta::as_integer<T>::type iT;
//   typedef typename boost::simd::meta::call<splat_(T)>::type r_t;
//   typedef typename boost::simd::meta::upgrade<T>::type u_t;
//   typedef T wished_r_t;


//   // return type conformity test 
//   BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl; 
//   double ulpd;
//   ulpd=0.0;


//   // specific values tests
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::One<T>()), boost::simd::One<r_t>());
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
// } // end of test for integer_

// BOOST_SIMD_TEST_CASE_TPL ( splat_real__1_0,  BOOST_SIMD_REAL_TYPES)
// {
  
//   using boost::simd::splat;
//   using boost::simd::tag::splat_;
//   typedef typename boost::simd::meta::as_integer<T>::type iT;
//   typedef typename boost::simd::meta::call<splat_(T)>::type r_t;
//   typedef typename boost::simd::meta::upgrade<T>::type u_t;
//   typedef T wished_r_t;


//   // return type conformity test 
//   BOOST_SIMD_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl; 
//   double ulpd;
//   ulpd=0.0;


//   // specific values tests
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::Inf<T>()), boost::simd::Inf<r_t>());
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::Minf<T>()), boost::simd::Minf<r_t>());
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::Nan<T>()), boost::simd::Nan<r_t>());
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::One<T>(),boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
//   BOOST_SIMD_TEST_EQUAL(splat(boost::simd::Zero<T>()), boost::simd::Zero<r_t>());
} // end of test for real_
