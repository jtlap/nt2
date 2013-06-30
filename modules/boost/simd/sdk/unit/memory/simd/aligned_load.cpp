//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <vector>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/preprocessor/stack_buffer.hpp>

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>

#include "../common/load_runner.hpp"
#include "../common/foo.hpp"
#include "fill.hpp"

NT2_TEST_CASE_TPL( load,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  aligned_load_runner< T          , native<T,ext_t>           >();
  aligned_load_runner< T          , pack<T>                   >();
  aligned_load_runner< logical<T> , native<logical<T>,ext_t>  >();
  aligned_load_runner< logical<T> , pack< logical<T> >        >();
}

NT2_TEST_CASE_TPL( load_offset,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  aligned_load_runner< T          , native<T,ext_t>           >(true);
  aligned_load_runner< T          , pack<T>                   >(true);
  aligned_load_runner< logical<T> , native<logical<T>,ext_t>  >(true);
  aligned_load_runner< logical<T> , pack< logical<T> >        >(true);
}

NT2_TEST_CASE( load_sequence_pointer )
{
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  aligned_load_runner< bar   , native<bar,ext_t>   >();
  aligned_load_runner< bar   , native<bar,ext_t>   >(true);
  aligned_load_runner< bar   , pack<bar>           >();
  aligned_load_runner< bar   , pack<bar>           >(true);
}

NT2_TEST_CASE_TPL( load_suboffset_periodic,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::meta::cardinal_of;
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;
  typedef typename cardinal_of< native<T,ext_t> >::type card;

  misaligned_load_runner< T         , native<T,ext_t>           >(card());
  misaligned_load_runner< T         , pack<T>                   >(card());
  misaligned_load_runner< logical<T>, native<logical<T>,ext_t>  >(card());
  misaligned_load_runner< logical<T>, pack<logical<T> >         >(card());
}

NT2_TEST_CASE_TPL( load_suboffset_forward,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  misaligned_load_runner< T         , native<T,ext_t>           >(boost::mpl::int_<1>());
  misaligned_load_runner< T         , pack<T>                   >(boost::mpl::int_<1>());
  misaligned_load_runner< logical<T>, native<logical<T>,ext_t>  >(boost::mpl::int_<1>());
  misaligned_load_runner< logical<T>, pack<logical<T> >         >(boost::mpl::int_<1>());
}

NT2_TEST_CASE_TPL( load_suboffset_backward,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  misaligned_load_runner< T         , native<T,ext_t>           >(boost::mpl::int_<1>());
  misaligned_load_runner< T         , pack<T>                   >(boost::mpl::int_<1>());
  misaligned_load_runner< logical<T>, native<logical<T>,ext_t>  >(boost::mpl::int_<-1>());
  misaligned_load_runner< logical<T>, pack<logical<T> >         >(boost::mpl::int_<-1>());
}

NT2_TEST_CASE_TPL( load_gather, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::aligned_load;
  using boost::simd::tag::aligned_load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                        vT;
  typedef typename boost::dispatch::meta::as_integer<vT>::type viT;

  typedef typename
          boost::dispatch::
          meta::call<aligned_load_(T*,viT,boost::dispatch::meta::as_<vT>)>::type rT;

  NT2_TEST_TYPE_IS( rT, vT );

  BOOST_SIMD_ALIGNED_STACK_BUFFER( data,  T, cardinal_of<vT>::value*3 );

  for(size_t i=0;i<cardinal_of<vT>::value*3;++i) data[i] = T(1+i);

  viT index;
  rT ref;

  // Spread out the gather values
  index[0] = cardinal_of<vT>::value*3 -1;
  index[cardinal_of<viT>::value-1] = 0;

  for(size_t i=1;i<cardinal_of<viT>::value-1;++i)
  {
    index[i] = T(i*(cardinal_of<vT>::value*3)/(cardinal_of<vT>::value-1));
  }

  for(size_t i=0;i<cardinal_of<vT>::value;++i) ref[i] = data[index[i]];

  rT v = boost::simd::aligned_load<vT>(&data[0], index);

  NT2_TEST_EQUAL(v , ref);
}

NT2_TEST_CASE( load_sequence )
{
  using boost::simd::aligned_load;
  using boost::simd::tag::aligned_load_;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  using boost::simd::allocator;
  using boost::fusion::make_vector;
  using boost::fusion::result_of::value_at;

  typedef BOOST_SIMD_DEFAULT_EXTENSION            ext_t;
  typedef native<foo,ext_t>                       vT;
  typedef value_at<vT,boost::mpl::int_<0> >::type foo0_t;
  typedef value_at<vT,boost::mpl::int_<1> >::type foo1_t;
  typedef value_at<vT,boost::mpl::int_<2> >::type foo2_t;

  static const size_t sz = cardinal_of< vT >::value;

  std::vector<short, allocator<short,sizeof(foo1_t)> > sdata(sz);
  std::vector<char , allocator<char ,sizeof(foo2_t)> > cdata(sz);
  std::vector<float, allocator<float,sizeof(foo1_t)> > fdata(sz);

  for(std::size_t i=0;i<sz;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    sdata[i] = short(1+i);
  }

  vT v = aligned_load<vT>(make_vector(&sdata[0], &fdata[0], &cdata[0]), 0);


  foo0_t sref = aligned_load<foo0_t>(&sdata[0]);
  foo1_t fref = aligned_load<foo1_t>(&fdata[0]);
  foo2_t cref = aligned_load<foo2_t>(&cdata[0]);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);
}
