//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/extract.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( extract, BOOST_SIMD_TYPES)
{
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef typename boost::dispatch::meta
                        ::call<extract_(T const&, int)>::type rcT;

  NT2_TEST_TYPE_IS( rcT, T const& );

  typedef typename boost::dispatch::meta
                        ::call<extract_(T&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, T& );

  T data, ref;
  T value = ref = T(42);

  data = extract(value, 0);

  NT2_TEST_EQUAL( data, ref   );
  NT2_TEST_EQUAL( data, value );

  extract(value, 0) = T(69);
  NT2_TEST_EQUAL( value, T(69) );
}

NT2_TEST_CASE_TPL( extract_logical, BOOST_SIMD_TYPES)
{
  using boost::simd::logical;
  using boost::simd::extract;
  using boost::simd::tag::extract_;

  typedef typename boost::dispatch::meta
                        ::call<extract_(logical<T> const&, int)>::type rcT;

  NT2_TEST_TYPE_IS( rcT, logical<T> const& );

  typedef typename boost::dispatch::meta
                        ::call<extract_(logical<T>&, int)>::type rT;

  NT2_TEST_TYPE_IS( rT, logical<T>& );

  logical<T> data, ref;
  logical<T> value = ref = true;

  data = extract(value, 0);

  NT2_TEST_EQUAL( data, ref   );
  NT2_TEST_EQUAL( data, value );

  extract(value, 0) = false;
  NT2_TEST_EQUAL( value, false );
}
