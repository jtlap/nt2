//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/insert.hpp>
#include <boost/simd/include/functions/extract.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/preprocessor/stack_buffer.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "../common/foo.hpp"

NT2_TEST_CASE_TPL( insert, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::native;
  using boost::simd::insert;
  using boost::simd::tag::insert_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef pack<T>                       pT;

  typedef typename boost::dispatch::meta::call<insert_(T, vT&, int)>::type rT;
  typedef typename boost::dispatch::meta::call<insert_(T, pT&, int)>::type qT;

  NT2_TEST_TYPE_IS( rT, void );
  NT2_TEST_TYPE_IS( qT, void );

  vT ref;
  vT value;
  pT rpck;
  pT pck;

  for(std::size_t i=0;i<vT::static_size;++i) rpck[i] = ref[i] = T(1+i);

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    insert(T(1+i),value, i);
    insert(T(1+i),pck, i);
  }

  NT2_TEST_EQUAL( ref, value );
  NT2_TEST_EQUAL( rpck, pck );
}

template<typename V> void insert_n(V& v, boost::mpl::int_<0> const& ) {}

template<typename V, int N>
void insert_n(V& v, boost::mpl::int_<N> const& )
{
  typedef typename V::value_type T;
  using boost::simd::insert;
  insert<N-1>(T(N),v);
  insert_n(v, boost::mpl::int_<N-1>());
}

NT2_TEST_CASE_TPL( insert_static, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::simd::native;
  using boost::simd::insert;
  using boost::simd::tag::insert_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;
  typedef pack<T>                       pT;

  typedef typename boost::dispatch::meta::call<insert_(T, vT&, boost::mpl::int_<0>)>::type rT;
  typedef typename boost::dispatch::meta::call<insert_(T, pT&, boost::mpl::int_<0>)>::type qT;

  NT2_TEST_TYPE_IS( rT, void );
  NT2_TEST_TYPE_IS( qT, void );

  vT ref;
  vT value;
  pT rpck;
  pT pck;

  for(std::size_t i=0;i<vT::static_size;++i) rpck[i] = ref[i] = T(1+i);

  insert_n(value, boost::mpl::int_<vT::static_size>() );
  insert_n(pck, boost::mpl::int_<vT::static_size>() );

  NT2_TEST_EQUAL( ref , value );
  NT2_TEST_EQUAL( rpck, pck );
}

NT2_TEST_CASE_TPL( insert_logical, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::pack;
  using boost::simd::native;
  using boost::simd::insert;
  using boost::simd::tag::insert_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>      vT;
  typedef pack< logical<T> >            pT;

  typedef typename boost::dispatch::meta
                        ::call<insert_(logical<T>, vT&, int)>::type rT;

  typedef typename boost::dispatch::meta
                        ::call<insert_(logical<T>, pT&, int)>::type qT;

  NT2_TEST_TYPE_IS( rT, void );
  NT2_TEST_TYPE_IS( qT, void );

  vT ref;
  vT value;
  pT rpck;
  pT pck;

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    ref[i]  = logical<T>(i%2);
    rpck[i] = logical<T>(i%2);
  }

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    insert(logical<T>(i%2),value, i);
    insert(logical<T>(i%2),pck, i);
  }

  NT2_TEST_EQUAL( ref , value );
  NT2_TEST_EQUAL( rpck, pck   );
}

NT2_TEST_CASE( insert_fusion )
{
  using boost::simd::native;
  using boost::simd::insert;
  using boost::simd::tag::insert_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo,ext_t>             vT;

  typedef boost::dispatch::meta
                        ::call<insert_(foo, vT&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, void );

  vT ref;
  vT value;

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    foo f  = { short(i+1), float(1.f/i), char('a'+1) };
    ref[i] = f;
  }

  for(std::size_t i=0;i<vT::static_size;++i)
  {
    foo f  = { short(i+1), float(1.f/i), char('a'+1) };
    insert(f,value, i);
  }

  NT2_TEST_EQUAL( ref, value );
}
