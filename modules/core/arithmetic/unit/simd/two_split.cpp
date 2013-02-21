//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/arithmetic/include/functions/two_split.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( two_split, NT2_SIMD_REAL_TYPES)
{
  using nt2::two_split;
  using boost::simd::native;
  using nt2::tag::two_split_;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> vT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<two_split_(vT)>::type)
                  , (std::pair<vT,vT>)
                  );

  vT eps_ = nt2::Eps<vT>();
  vT one_ = nt2::One<vT>();

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
