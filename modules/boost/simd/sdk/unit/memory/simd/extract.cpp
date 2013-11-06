//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/extract.hpp>
#include <boost/simd/include/functions/insert.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../common/foo.hpp"

NT2_TEST_CASE_TPL( extract, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::native;
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef pack<T>                       pT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT const&, int)>::type rT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(pT const&, int)>::type qT;

  NT2_TEST_TYPE_IS( rT, T );
  NT2_TEST_TYPE_IS( qT, T );

  vT value;
  pT pck;

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    value[i] = T(1+i);
    pck[i] = T(1+i);
  }

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    NT2_TEST_EQUAL( extract(value, i), T(1+i) );
    NT2_TEST_EQUAL( extract(pck, i), T(1+i) );
  }
}

template<typename V> void extract_n(V const& v, boost::mpl::int_<0> const& ) {}

template<typename V, int N>
void extract_n(V const& v, boost::mpl::int_<N> const& )
{
  typedef typename V::value_type T;
  using boost::simd::extract;
  NT2_TEST_EQUAL( extract<N-1>(v), T(N) );
  extract_n(v, boost::mpl::int_<N-1>());
}

NT2_TEST_CASE_TPL( extract_static, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::native;
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef pack<T>                       pT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT const&, boost::mpl::int_<0>)>::type rT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(pT const&, boost::mpl::int_<0>)>::type qT;

  NT2_TEST_TYPE_IS( rT, T );
  NT2_TEST_TYPE_IS( qT, T );

  vT value;
  pT pck;

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    value[i] = T(1+i);
    pck[i] = T(1+i);
  }

  extract_n(value, boost::mpl::int_<vT::static_size>() );
  extract_n(pck, boost::mpl::int_<vT::static_size>() );
}

NT2_TEST_CASE_TPL( static_extract, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::native;
  using boost::simd::extract;
  using boost::simd::tag::extract_;
  using boost::mpl::int_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef pack<T>                       pT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT const&, int_<0>)>::type rT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(pT const&, int_<0>)>::type qT;

  NT2_TEST_TYPE_IS( rT, T );
  NT2_TEST_TYPE_IS( qT, T );

  vT value;
  pT pck;

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    value[i] = T(1+i);
    pck[i] = T(1+i);
  }

  NT2_TEST_EQUAL( extract<0>(value), T(1) );
  NT2_TEST_EQUAL( extract<0>(pck)  , T(1) );
  NT2_TEST_EQUAL( extract<vT::static_size-1>(value), T(vT::static_size) );
  NT2_TEST_EQUAL( extract<vT::static_size-1>(pck)  , T(vT::static_size) );
}

NT2_TEST_CASE_TPL( extract_logical, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::pack;
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>      vT;
  typedef pack< logical<T> >            pT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT const&, int)>::type rT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(pT const&, int)>::type qT;

  NT2_TEST_TYPE_IS( rT, logical<T> );
  NT2_TEST_TYPE_IS( qT, logical<T> );

  vT value;
  pT pck;

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    value[i] = logical<T>(i%2);
    pck[i] = logical<T>(i%2);
  }

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    NT2_TEST_EQUAL( extract(value, i), logical<T>(i%2) );
    NT2_TEST_EQUAL( extract(pck, i)  , logical<T>(i%2) );
  }
}

NT2_TEST_CASE( extract_fusion )
{
  using boost::simd::native;
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo,ext_t>             vT;

  typedef boost::dispatch::meta
                        ::call<extract_(vT const&, int)>::type rcT;

  NT2_TEST_TYPE_IS( rcT, foo );

  typedef boost::dispatch::meta
                        ::call<extract_(vT&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, foo );

  vT value;

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    foo f = { short(i+1), float(1.f/i), char('a'+1) };
    value[i] = f;
  }

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    NT2_TEST_EQUAL( extract(value, i).d, short(i+1));
    NT2_TEST_EQUAL( extract(value, i).f, float(1.f/i));
    NT2_TEST_EQUAL( extract(value, i).c, char('a'+1));
  }
}
