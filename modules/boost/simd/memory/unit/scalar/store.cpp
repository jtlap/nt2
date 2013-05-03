//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>

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
  using boost::simd::tag::store_;
  using boost::simd::load;
  using boost::fusion::make_vector;
  using boost::fusion::result_of::value_at;

  static const size_t sz = 5;

  char  cdata[sz];
  float fdata[sz];
  short sdata[sz];

  char  scdata[sz];
  float sfdata[sz];
  short ssdata[sz];

  for(std::size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    sdata[i] = short(1+i);
  }

  for(std::size_t i=0;i<sz;++i)
  {
    foo v = load<foo>(boost::fusion::make_vector(&sdata[i], &fdata[i], &cdata[i]), 0);
    store(v, boost::fusion::make_vector(&ssdata[i], &sfdata[i], &scdata[i]), 0);

    typedef value_at<foo,boost::mpl::int_<0> >::type foo0_t;
    typedef value_at<foo,boost::mpl::int_<1> >::type foo1_t;
    typedef value_at<foo,boost::mpl::int_<2> >::type foo2_t;

    foo0_t sref = load<foo0_t>(&ssdata[i]);
    foo1_t fref = load<foo1_t>(&sfdata[i]);
    foo2_t cref = load<foo2_t>(&scdata[i]);

    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);
  }
}
