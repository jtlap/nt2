//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
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
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  aligned_store_runner< T         , native<T,ext_t>           >();
  aligned_store_runner< T         , pack<T>                   >();
  aligned_store_runner< logical<T>, native<logical<T>,ext_t>  >();
  aligned_store_runner< logical<T>, pack< logical<T> >        >();
}

NT2_TEST_CASE_TPL( store_offset,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  aligned_store_runner< T         , native<T,ext_t>           >(true);
  aligned_store_runner< T         , pack<T>                   >(true);
  aligned_store_runner< logical<T>, native<logical<T>,ext_t>  >(true);
  aligned_store_runner< logical<T>, pack< logical<T> >        >(true);
}

NT2_TEST_CASE( store_sequence_pointer )
{
  using boost::simd::pack;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  aligned_store_runner< bar, native<bar,ext_t> >();
  aligned_store_runner< bar, pack<bar> >();
  aligned_store_runner< bar, native<bar,ext_t> >(true);
  aligned_store_runner< bar, pack<bar> >(true);
}

NT2_TEST_CASE_TPL(store_scatter, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::aligned_store;
  using boost::simd::aligned_load;
  using boost::simd::tag::aligned_store_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type viT;
  typedef typename boost::dispatch::meta::as_integer<T>::type  iT;

  typedef typename boost::dispatch::meta::call<aligned_store_(vT,T*,viT)>::type  rT;

  NT2_TEST_TYPE_IS( rT, void );

  std::size_t card = cardinal_of<vT>::value;
  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, card*3 );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( out ,  T, card*3 );

  for(size_t i=0;i<cardinal_of<vT>::value*3;++i)
  {
    data[i] = T(1+i);
    out[i]   = T(0);
  }

  viT index;

  // Spread out the scatter values
  index[0] = cardinal_of<vT>::value*3 -1;
  index[cardinal_of<viT>::value-1] = 0;

  for(std::size_t i=1;i<cardinal_of<viT>::value-1;++i)
  {
    index[i] = iT(i*(cardinal_of<vT>::value*3)/(cardinal_of<vT>::value-1));
  }

  vT v = aligned_load<vT>(&data[0]);
  aligned_store(v,&out[0],index);
  vT ref = aligned_load<vT>(&out[0],index);

  NT2_TEST_EQUAL( ref, v );
}

NT2_TEST_CASE( store_sequence )
{
  using boost::simd::aligned_store;
  using boost::simd::tag::aligned_store_;
  using boost::simd::aligned_load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::fusion::make_vector;
  using boost::fusion::result_of::value_at;

  typedef BOOST_SIMD_DEFAULT_EXTENSION            ext_t;
  typedef native<foo,ext_t>                       vT;
  typedef value_at<vT,boost::mpl::int_<0> >::type foo0_t;
  typedef value_at<vT,boost::mpl::int_<1> >::type foo1_t;
  typedef value_at<vT,boost::mpl::int_<2> >::type foo2_t;

  static const size_t sz = cardinal_of< vT >::value;

  BOOST_SIMD_ALIGNED_STACK_BUFFER( cdata, char  , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( fdata, float , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( sdata, short , sz );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( scdata, char  , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( sfdata, float , sz );
  BOOST_SIMD_ALIGNED_STACK_BUFFER( ssdata, short , sz );

  for(std::size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    sdata[i] = short(1+i);
  }

  vT v = aligned_load<vT>(boost::fusion::make_vector(&sdata[0], &fdata[0], &cdata[0]), 0);
  aligned_store(v, boost::fusion::make_vector(&ssdata[0], &sfdata[0], &scdata[0]), 0);

  typedef value_at<vT,boost::mpl::int_<0> >::type foo0_t;
  typedef value_at<vT,boost::mpl::int_<1> >::type foo1_t;
  typedef value_at<vT,boost::mpl::int_<2> >::type foo2_t;

  foo0_t sref = aligned_load<foo0_t>(&ssdata[0]);
  foo1_t fref = aligned_load<foo1_t>(&sfdata[0]);
  foo2_t cref = aligned_load<foo2_t>(&scdata[0]);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);
}
