//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - store/simd Mode"

#include <boost/simd/include/functions/store.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>
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
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  store_runner< T  , native<T,ext_t>   >();
  store_runner< T  , pack<T>           >();
}

NT2_TEST_CASE_TPL( store_offset,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  store_runner< T  , native<T,ext_t>   >(true);
  store_runner< T  , pack<T>           >(true);
}

NT2_TEST_CASE( store_sequence_pointer )
{
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  store_runner< foo, native<foo,ext_t> >();
  store_runner< foo, native<foo,ext_t> >(true);
}

NT2_TEST_CASE( store_sequence )
{
  using boost::simd::store;
  using boost::simd::load;
  using boost::simd::tag::store_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::fusion::make_vector;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo, ext_t> seq_t;

  static const size_t sz = cardinal_of< seq_t >::value;
  short  sdata[ sz ];
  float  fdata[ sz ];
  char   cdata[ sz ];

  short  ssdata[ sz ];
  float  sfdata[ sz ];
  char   scdata[ sz ];

  for(size_t i=0;i<sz;++i)
  {
    sdata[i] = short(10+i);
    fdata[i] = float(1+i);
    cdata[i] = char(65+i);
  }

  seq_t v = load<seq_t>(make_vector(&sdata[0], &fdata[0], &cdata[0]), 0);
  store(v, make_vector(&ssdata[0], &sfdata[0], &scdata[0]));

  for(size_t j=0;j<sz;++j)
  {
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v)[j] , ssdata[j]);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v)[j] , sfdata[j]);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v)[j] , scdata[j]);
  }
}
