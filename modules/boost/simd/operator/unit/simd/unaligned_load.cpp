//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - unaligned_load/simd Mode"

#include <iostream>
#include <boost/simd/include/functions/unaligned_load.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

NT2_TEST_CASE_TPL( unaligned_load,  BOOST_SIMD_TYPES)
{
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_load_;
  using boost::simd::unaligned_load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  typedef native<T,ext_t>                        vT;
  typedef typename
          boost::dispatch::
          meta::call<unaligned_load_(T*,int,boost::dispatch::meta::as_<vT>)>::type r_t;

  NT2_TEST( (boost::is_same<vT,r_t>::value) );

  T data[ cardinal_of<vT>::value*3 ];
  for(int i=0;i<cardinal_of<vT>::value*3;++i) data[i] = 1+i;

  for(int i=0;i<3;++i)
  {
    r_t v = boost::simd::unaligned_load<vT>(&data[i*cardinal_of<vT>::value]);
    for(int j=0;j<cardinal_of<vT>::value;++j)
      NT2_TEST_EQUAL(v[j] , data[j+i*cardinal_of<vT>::value]);
  }
}

NT2_TEST_CASE_TPL( unaligned_load_offset,  BOOST_SIMD_TYPES)
{
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_load_;
  using boost::simd::unaligned_load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  typedef native<T,ext_t>                        vT;
  typedef typename
          boost::dispatch::
          meta::call<unaligned_load_(T*,int,boost::dispatch::meta::as_<vT>)>::type r_t;

  NT2_TEST( (boost::is_same<vT,r_t>::value) );

  T data[ cardinal_of<vT>::value*3 ];
  for(int i=0;i<cardinal_of<vT>::value*3;++i) data[i] = 1+i;

  {
    int offset = -int(cardinal_of<vT>::value);
    r_t v = boost::simd::unaligned_load<vT>(&data[cardinal_of<vT>::value],offset);
    for(int j=0;j<cardinal_of<vT>::value;++j)
      NT2_TEST_EQUAL(v[j] , data[j]);
  }

  {
    r_t v = boost::simd::unaligned_load<vT>(&data[cardinal_of<vT>::value], 0);
    for(int j=0;j<cardinal_of<vT>::value;++j)
      NT2_TEST_EQUAL(v[j] , data[j+cardinal_of<vT>::value]);
  }

  {
    r_t v = boost::simd::unaligned_load<vT>(&data[cardinal_of<vT>::value],+cardinal_of<vT>::value);
    for(int j=0;j<cardinal_of<vT>::value;++j)
      NT2_TEST_EQUAL(v[j] , data[j+2*cardinal_of<vT>::value]);
  }
}

NT2_TEST_CASE_TPL( unaligned_load_suboffset,  BOOST_SIMD_TYPES)
{
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_load_;
  using boost::simd::unaligned_load;
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;

  typedef native<T,ext_t>                        vT;
  typedef typename
          boost::dispatch::
          meta::call<unaligned_load_(T*,int,boost::dispatch::meta::as_<vT>, boost::mpl::int_<1>)>::type r_t;

  NT2_TEST( (boost::is_same<vT,r_t>::value) );

  T data[ cardinal_of<vT>::value*3 ];
  for(int i=0;i<cardinal_of<vT>::value*3;++i) data[i] = 1+i;

  {
    r_t v = boost::simd::unaligned_load<vT,1>(&data[0]);
    for(int j=0;j<cardinal_of<vT>::value;++j)
      NT2_TEST_EQUAL(v[j] , data[j+1]);
  }

  {
    r_t v = boost::simd::unaligned_load<vT,1>(&data[0], cardinal_of<vT>::value);
    for(int j=0;j<cardinal_of<vT>::value;++j)
      NT2_TEST_EQUAL(v[j] , data[j+cardinal_of<vT>::value+1]);
  }

  {
    r_t v = boost::simd::unaligned_load<vT,-1>(&data[0],2*cardinal_of<vT>::value);
    for(int j=0;j<cardinal_of<vT>::value;++j)
      NT2_TEST_EQUAL(v[j] , data[j+2*cardinal_of<vT>::value-1]);
  }
}

NT2_TEST_CASE_TPL( unaligned_load_gather, BOOST_SIMD_TYPES)
{
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_load_;
  using boost::simd::unaligned_load;
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
  for(int i=0;i<cardinal_of<vT>::value*3;++i) data[i] = 1+i;

  viT index;
  for(int i=0;i<cardinal_of<viT>::value;++i)
    index[i] = rand() % (cardinal_of<vT>::value*3);

  r_t v = boost::simd::unaligned_load<vT>(&data[0], index);

  for(int j=0;j<cardinal_of<vT>::value;++j)
  {
    NT2_TEST_EQUAL(v[j] , data[index[j]]);
  }
}
