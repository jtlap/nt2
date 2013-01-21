//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 operator toolbox - unaligned_store/scalar Mode"

#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL(unaligned_store, BOOST_SIMD_TYPES)
{
  using boost::simd::unaligned_store;

  T data[5];
  for(boost::simd::int32_t i=0;i<5;++i) unaligned_store(static_cast<T>(i),&data[0],i);
  NT2_TEST_EQUAL( data[0], T(0) );
  NT2_TEST_EQUAL( data[1], T(1) );
  NT2_TEST_EQUAL( data[2], T(2) );
  NT2_TEST_EQUAL( data[3], T(3) );
  NT2_TEST_EQUAL( data[4], T(4) );
}

NT2_TEST_CASE( unaligned_store_sequence )
{
  using boost::simd::unaligned_store;
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_store_;

  double d = 3.4;
  float  f = 1.8;
  char   c = 'a';
  double sd;
  float  sf;
  char   sc;

  boost::fusion::vector<double,float,char> v;

  v = unaligned_load< boost::fusion::vector<double,float,char> >(boost::fusion::make_vector(&d, &f, &c), 0);
  unaligned_store(v,boost::fusion::make_vector(&sd, &sf, &sc),0);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sd);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , sf);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , sc);
}

NT2_TEST_CASE( unaligned_store_pointer_of_sequence )
{
  using boost::simd::unaligned_store;
  using boost::simd::unaligned_load;
  using boost::simd::tag::unaligned_store_;

  double d = 3.4;
  float  f = 1.8;
  char   c = 'a';
  double sd;
  float  sf;
  char   sc;

  boost::fusion::vector<double,float,char> v,dest;
  boost::fusion::vector<double,float,char> s(d,f,c);

  v = unaligned_load< boost::fusion::vector<double,float,char> >(&s, 0);
  unaligned_store(v,&dest,0);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(dest) , d);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(dest) , f);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(dest) , c);
}
