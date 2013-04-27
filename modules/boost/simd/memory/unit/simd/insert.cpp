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
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/memory/stack_buffer.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

NT2_TEST_CASE_TPL( insert, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::insert;
  using boost::simd::tag::insert_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               vT;

  typedef typename boost::dispatch::meta::call<insert_(T, vT&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, vT& );

  vT ref;
  vT value;

  for(std::size_t i=0;i<vT::static_size;++i) ref[i] = T(1+i);

  for(std::size_t i=0;i<vT::static_size;++i)
    insert(T(1+i),value, i);

  NT2_TEST_EQUAL( ref, value );
}

NT2_TEST_CASE_TPL( insert_logical, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::insert;
  using boost::simd::tag::insert_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<logical<T>,ext_t>      vT;

  typedef typename boost::dispatch::meta
                        ::call<insert_(logical<T>, vT&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, vT& );

  vT ref;
  vT value;

  for(std::size_t i=0;i<vT::static_size;++i) ref[i] = logical<T>(i%2);

  for(std::size_t i=0;i<vT::static_size;++i)
    insert(logical<T>(i%2),value, i);

  NT2_TEST_EQUAL( ref, value );
}

struct foo { short d; float f; char c; };
BOOST_FUSION_ADAPT_STRUCT(foo,(short,d)(float,f)(char,c))

NT2_TEST_CASE( insert_fusion )
{
  using boost::simd::native;
  using boost::simd::insert;
  using boost::simd::tag::insert_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<foo,ext_t>             vT;

  typedef boost::dispatch::meta
                        ::call<insert_(foo, vT&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, vT& );

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
