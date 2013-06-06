//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/stream.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(stream, BOOST_SIMD_TYPES)
{
  using boost::simd::stream;

  T data[5];

  for(boost::simd::int32_t i=0;i<5;++i)
    stream(static_cast<T>(2-i),&data[i]);

  NT2_TEST_EQUAL( data[0], T(2)  );
  NT2_TEST_EQUAL( data[1], T(1)  );
  NT2_TEST_EQUAL( data[2], T(0)  );
  NT2_TEST_EQUAL( data[3], T(-1) );
  NT2_TEST_EQUAL( data[4], T(-2) );
}

NT2_TEST_CASE_TPL(stream_offset, BOOST_SIMD_TYPES)
{
  using boost::simd::stream;

  T data[5];

  for(boost::simd::int32_t i=0;i<5;++i)
    stream(static_cast<T>(2-i),&data[0],i);

  NT2_TEST_EQUAL( data[0], T(2)  );
  NT2_TEST_EQUAL( data[1], T(1)  );
  NT2_TEST_EQUAL( data[2], T(0)  );
  NT2_TEST_EQUAL( data[3], T(-1) );
  NT2_TEST_EQUAL( data[4], T(-2) );
}
