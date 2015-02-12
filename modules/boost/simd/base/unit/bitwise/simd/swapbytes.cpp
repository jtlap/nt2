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
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/enumerate.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>


NT2_TEST_CASE_TPL ( swapbytes,   BOOST_SIMD_SIMD_INTEGRAL_TYPES)
{

  using boost::simd::swapbytes;
  using boost::simd::tag::swapbytes_;
  typedef BOOST_SIMD_DEFAULT_EXTENSION                             ext_t;
  typedef boost::simd::native<T,ext_t>                                vT;

  // specific values tests
  vT a =  boost::simd::enumerate<vT>(0xF0);
  for(std::size_t i=0; i < sizeof(T) ; i++)
  {
    vT za =  boost::simd::shl(a, 8*i);
    NT2_TEST_EQUAL(swapbytes(za), boost::simd::shl(a,(sizeof(T)-i-1)*8));
  }

} // end of test for unsigned_int_




