//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/memory/stack_buffer.hpp>

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include "../common/load_runner.hpp"
#include "../common/foo.hpp"
#include "fill.hpp"

NT2_TEST_CASE_TPL( unaligned_load,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  unaligned_load_runner< T  , native<T,ext_t>   >();
  unaligned_load_runner< logical<T>  , native<logical<T>,ext_t>   >();
  unaligned_load_runner< foo, native<foo,ext_t> >();
  unaligned_load_runner< T  , pack<T>           >();
}

NT2_TEST_CASE_TPL( unaligned_load_offset,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  unaligned_load_runner< T   , native<T,ext_t>   >(true);
  unaligned_load_runner< logical<T>  , native<logical<T>,ext_t>   >(true);
  unaligned_load_runner< foo , native<foo,ext_t> >(true);
  unaligned_load_runner< T   , pack<T>           >(true);
}

NT2_TEST_CASE_TPL( unaligned_load_gather, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  typedef native<T,ext_t>                                       vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type   iT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type viT;
  typedef typename
          boost::dispatch::
          meta::call<unaligned_load_(T*,viT,boost::dispatch::meta::as_<vT>)>::type r_t;

  srand(time(NULL));

  NT2_TEST( (boost::is_same<vT,r_t>::value) );

  T data[ cardinal_of<vT>::value*3 ];
  for(size_t i=0;i<cardinal_of<vT>::value*3;++i) data[i] = T(1+i);

  viT index;
  for(size_t i=0;i<cardinal_of<viT>::value;++i)
    index[i] = rand() % (cardinal_of<vT>::value*3);

  r_t v = boost::simd::unaligned_load<vT>(&data[0], index);

  for(size_t j=0;j<cardinal_of<vT>::value;++j)
  {
    NT2_TEST_EQUAL(v[j] , data[index[j]]);
  }
}

NT2_TEST_CASE( unaligned_load_sequence )
{
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::int16_t;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  typedef native<foo, ext_t> seq_t;
  static const size_t sz = cardinal_of< seq_t >::value;

  char     cdata[ sz ];
  float    fdata[ sz ];
  int16_t  ddata[ sz ];

  for(size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    ddata[i] = int16_t(1+i);
  }

  seq_t v = unaligned_load<seq_t>(boost::fusion::make_vector(&ddata[0], &fdata[0], &cdata[0]), 0);

  for(size_t i=0;i<sz;++i)
  {
    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v)[i] , ddata[i]);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v)[i] , fdata[i]);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v)[i] , cdata[i]);
  }
}
