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
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

NT2_TEST_CASE_TPL( extract, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT const&, int)>::type rcT;

  NT2_TEST_TYPE_IS( rcT, T const& );

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, T& );

  vT value;

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    value[i] = T(1+i);
  }

  for(std::size_t i=0;i<vT::static_size;i++)
  {
    NT2_TEST_EQUAL( extract(value, i), T(1+i) );

    extract(value, i) = T(2*(i+1));
    NT2_TEST_EQUAL( value[i], T(2*(i+1)) );
  }
}

NT2_TEST_CASE_TPL( extract_logical, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>      vT;

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT const&, int)>::type rcT;

  NT2_TEST_TYPE_IS( rcT, logical<T> );

  typedef typename boost::dispatch::meta
                        ::call<extract_(vT&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, logical<T> );

  vT value;

  for(std::size_t i=0;i<vT::static_size;i++)
    value[i] = logical<T>(i%2);

  for(std::size_t i=0;i<vT::static_size;i++)
    NT2_TEST_EQUAL( extract(value, i), i%2 );
}

struct foo { short d; float f; char c; };
BOOST_FUSION_ADAPT_STRUCT(foo,(short,d)(float,f)(char,c))

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
