//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/bitwise/include/functions/swapbytes.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <boost/simd/include/functions/shift_left.hpp>


NT2_TEST_CASE_TPL ( swapbytes_uit,   BOOST_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::swapbytes;
  using boost::simd::tag::swapbytes_;
  typedef typename boost::dispatch::meta::call<swapbytes_(T)>::type r_t;
  typedef T                                                  wished_r_t;


  // return type conformity test
  NT2_TEST_TYPE_IS( r_t, wished_r_t );

  // specific values tests
  T a =  T(0xFF);
  for(std::size_t i=0; i < sizeof(T) ; i++)
  {
    T za =  boost::simd::shl(a, 8*i);
    NT2_TEST_EQUAL(swapbytes(za), T(boost::simd::shl(a,(sizeof(T)-i-1)*8)));
  }
} // end of test for unsigned_int_

