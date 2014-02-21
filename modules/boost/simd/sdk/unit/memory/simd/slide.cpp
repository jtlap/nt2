//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/slide.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

template<typename T,typename U, int Card>
struct test_slide1
{
  test_slide1(T const& l_, U* d_) : l(l_), data(d_) {}

  template<int I> BOOST_FORCEINLINE void operator()() const
  {
    using boost::simd::load;
    using boost::simd::slide;

    NT2_TEST_EQUAL( slide<I-Card>(l), load<T>(&data[I]) );
  }

  T   l;
  U*  data;
};

template<typename T,typename U>
struct test_slide2
{
  test_slide2(T const& l_, T const& r_, U* d_) : l(l_), r(r_), data(d_) {}

  template<int I> BOOST_FORCEINLINE void operator()() const
  {
    using boost::simd::load;
    using boost::simd::slide;

    NT2_TEST_EQUAL( slide<I>(l,r), load<T>(&data[I]) );
  }

  T   l,r;
  U*  data;
};

NT2_TEST_CASE_TPL( slide, BOOST_SIMD_SIMD_TYPES )
{
  using boost::mpl::int_;
  using boost::simd::native;
  using boost::simd::slide;
  using boost::simd::load;
  using boost::simd::tag::slide_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  static const std::size_t card = vT::static_size;

  T data[3*card];

  for(std::size_t i = 0;i<card;++i) data[       i] = T(0);
  for(std::size_t i = 0;i<card;++i) data[  card+i] = T(1+i);
  for(std::size_t i = 0;i<card;++i) data[2*card+i] = T(0);

  typedef typename boost::dispatch::meta::call<slide_(vT, int_<0>)>::type rT;

  NT2_TEST_TYPE_IS( rT, vT );

  vT vl = load<vT>(&data[card]);

  boost::simd::meta::iterate< 2*card+1 >( test_slide1<vT,T,card>(vl,&data[0]));
}

NT2_TEST_CASE_TPL( binary_slide, BOOST_SIMD_SIMD_TYPES )
{
  using boost::mpl::int_;
  using boost::simd::native;
  using boost::simd::slide;
  using boost::simd::load;
  using boost::simd::tag::slide_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  static const std::size_t card = vT::static_size;

  T data[2*card];

  for(std::size_t i = 0;i<2*card;++i) data[i] = T(1+i);

  typedef typename boost::dispatch::meta::call<slide_(vT, vT, int_<0>)>::type rT;

  NT2_TEST_TYPE_IS( rT, vT );

  vT vl = load<vT>(&data[0]);
  vT vr = load<vT>(&data[card]);

  boost::simd::meta::iterate< card+1 >( test_slide2<vT,T>(vl,vr,&data[0]));
}
