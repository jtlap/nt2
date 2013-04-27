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

NT2_TEST_CASE_TPL( load_suboffset_forward,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;

  misload_runner< T, T >(boost::mpl::int_<1>());
  //misload_runner< foo, foo >(boost::mpl::int_<1>());
  misload_runner< logical<T>, logical<T> >(boost::mpl::int_<1>());
}

NT2_TEST_CASE_TPL( load_suboffset_backward,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;

  misload_runner< T, T >(boost::mpl::int_<-1>());
  // misload_runner< foo, foo >(boost::mpl::int_<-1>());
  misload_runner< logical<T>, logical<T> >(boost::mpl::int_<-1>());
}

NT2_TEST_CASE( load_sequence )
{
  using boost::simd::load;
  using boost::simd::tag::load_;
  using boost::fusion::make_vector;
  using boost::fusion::vector;
  using boost::fusion::result_of::value_at;

  char  cdata[3];
  float fdata[3];
  short sdata[3];

  for(std::size_t i=0;i<3;++i)
  {
    cdata[i] = char(1+i);
    fdata[i] = float(1+i);
    sdata[i] = short(1+i);
  }

  typedef  boost::dispatch::meta
                  ::call<load_( vector<short,float,char>
                              , boost::dispatch::meta::as_<foo>
                              )
                        >::type                     rT;

  NT2_TEST_TYPE_IS( rT, foo );

  typedef boost::dispatch::meta
                ::call<load_( vector<short,float,char>
                            , int
                            , boost::dispatch::meta::as_<foo>
                            )
                      >::type                     riT;

  NT2_TEST_TYPE_IS( riT, foo );

  foo v = load<foo>(make_vector(&sdata[0], &fdata[0], &cdata[0]) );

  typedef value_at<foo,boost::mpl::int_<0> >::type foo0_t;
  typedef value_at<foo,boost::mpl::int_<1> >::type foo1_t;
  typedef value_at<foo,boost::mpl::int_<2> >::type foo2_t;

  foo0_t sref = load<foo0_t>(&sdata[0]);
  foo1_t fref = load<foo1_t>(&fdata[0]);
  foo2_t cref = load<foo2_t>(&cdata[0]);

  NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
  NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
  NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);

  for(std::size_t i=0;i<3;++i)
  {
    foo v = load<foo>(make_vector(&sdata[0], &fdata[0], &cdata[0]), i );

    typedef value_at<foo,boost::mpl::int_<0> >::type foo0_t;
    typedef value_at<foo,boost::mpl::int_<1> >::type foo1_t;
    typedef value_at<foo,boost::mpl::int_<2> >::type foo2_t;

    foo0_t sref = load<foo0_t>(&sdata[0],i);
    foo1_t fref = load<foo1_t>(&fdata[0],i);
    foo2_t cref = load<foo2_t>(&cdata[0],i);

    NT2_TEST_EQUAL(boost::fusion::at_c<0>(v) , sref);
    NT2_TEST_EQUAL(boost::fusion::at_c<1>(v) , fref);
    NT2_TEST_EQUAL(boost::fusion::at_c<2>(v) , cref);
  }
}
