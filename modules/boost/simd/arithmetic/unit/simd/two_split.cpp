//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/toolbox/arithmetic/include/functions/two_split.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/constants/eps.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/functions/unary_minus.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( two_split, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::two_split;
  using boost::simd::native;
  using boost::simd::tag::two_split_;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> vT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<two_split_(vT)>::type)
                  , (std::pair<vT,vT>)
                  );

  vT eps_ = boost::simd::Eps<vT>();
  vT one_ = boost::simd::One<vT>();

  {
    vT f,s;

    two_split(one_-eps_, f, s);
    NT2_TEST_EQUAL(f, one_);
    NT2_TEST_EQUAL(s, -eps_);
  }

  {
    vT f,s;

    f = two_split(one_-eps_, s);
    NT2_TEST_EQUAL(f, one_);
    NT2_TEST_EQUAL(s, -eps_);
  }

  {
    vT f,s;

    boost::fusion::vector_tie(f,s) = two_split(one_-eps_);
    NT2_TEST_EQUAL(f, one_);
    NT2_TEST_EQUAL(s, -eps_);
  }

  {
    std::pair<vT,vT> p;

    p = two_split(one_-eps_);
    NT2_TEST_EQUAL(p.first, one_);
    NT2_TEST_EQUAL(p.second, -eps_);
  }
}
