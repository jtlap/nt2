//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include "../common/load_runner.hpp"
#include "../common/foo.hpp"

NT2_TEST_CASE_TPL( load,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;

  load_runner< T, T >();
  load_runner< foo, foo >();
  load_runner< logical<T>, logical<T> >();
}

NT2_TEST_CASE_TPL( load_offset,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;

  load_runner< T, T >(true);
  load_runner< foo, foo >(true);
  load_runner< logical<T>, logical<T> >(true);
}

NT2_TEST_CASE( load_sequence )
{
  using boost::fusion::make_vector;
  using boost::simd::load;
  using boost::simd::tag::load_;

  static const size_t sz = 3;

  char     cdata[ sz ];
  float    fdata[ sz ];
  int16_t  ddata[ sz ];

  for(size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    ddata[i] = short(1+i);
  }

  for(size_t i=0;i<sz;++i)
  {
    foo v = load<foo>(make_vector(&ddata[0], &fdata[0], &cdata[0]), i);
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , ddata[i]);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fdata[i]);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cdata[i]);
  }
}
