//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/slide.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( slide, BOOST_SIMD_TYPES)
{
  using boost::mpl::int_;
  using boost::simd::slide;
  using boost::simd::tag::slide_;

  typedef typename boost::dispatch::meta::call<slide_(T, T, int_<0>)>::type rT;

  NT2_TEST_TYPE_IS( rT, T );

  T l = T(42);
  T r = T(69);

  NT2_TEST_EQUAL( slide<-1>(l,r), T(0)  );
  NT2_TEST_EQUAL( slide< 0>(l,r), l     );
  NT2_TEST_EQUAL( slide< 1>(l,r), r     );
  NT2_TEST_EQUAL( slide< 2>(l,r), T(0)  );
}
