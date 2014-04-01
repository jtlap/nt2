//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - store/scalar Mode"

#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/load.hpp>

#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../common/store_runner.hpp"
#include "../common/foo.hpp"

NT2_TEST_CASE_TPL( store,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;

  store_runner< T, T >();
  store_runner< logical<T>, logical<T> >();
}

NT2_TEST_CASE_TPL( store_offset,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;

  store_runner< T, T >(true);
  store_runner< logical<T>, logical<T> >(true);
}

NT2_TEST_CASE( store_sequence_pointer )
{
  store_runner< foo, foo >();
  store_runner< foo, foo >(true);
}

NT2_TEST_CASE( store_sequence )
{
  using boost::simd::store;
  using boost::simd::load;
  using boost::simd::tag::store_;
  using boost::fusion::vector;
  using boost::fusion::make_vector;

  double d = 3.4;
  float  f = 1.8f;
  char   c = 'a';
  double sd;
  float  sf;
  char   sc;

  vector<double,float,char> v;

  v = load< vector<double,float,char> >(make_vector(&d, &f, &c), 0);
  store(v,make_vector(&sd, &sf, &sc),0);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sd);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , sf);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , sc);
}

NT2_TEST_CASE_TPL( mask_store ,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  logical<T> mask = logical<T>(1);
  mask_store_runner< T, T, logical<T> >(mask);

  mask = logical<T>(0);
  mask_store_runner< T, T, logical<T> >(mask);
}

NT2_TEST_CASE_TPL( mask_store_offset ,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  logical<T> mask = logical<T>(1);
  mask_store_runner< T, T, logical<T> >(mask, true);

  mask = logical<T>(0);
  mask_store_runner< T, T, logical<T> >(mask, true);
}
