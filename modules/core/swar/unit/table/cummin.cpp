//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cummin.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/include/functions/rand.hpp>

template < class A > A byhands(const A & a)
{
  A that = a;
  for(size_t i=2; i <= numel(a); ++i)
    that(i) = boost::simd::min(that(i-1), that(i));
  return that;
}

NT2_TEST_CASE_TPL( cummin,  BOOST_SIMD_SIMD_REAL_TYPES )
{
  using nt2::table;
  using nt2::cummin;

  table<T> a = nt2::rand(1,25,nt2::meta::as_<T>());
  table<T> rb =  byhands(a);
  table<T> b = cummin(a);
  NT2_TEST_EQUAL(b, rb);
}

