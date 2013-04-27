//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/ieee/include/functions/frexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( frexp, NT2_SIMD_REAL_TYPES)
{
  using nt2::frexp;
  using nt2::tag::frexp_;
  using boost::simd::native;
  typedef native<T,NT2_SIMD_DEFAULT_EXTENSION>            vT;
  typedef typename nt2::meta::as_integer<vT,signed>::type viT;

  NT2_TEST_TYPE_IS( (typename nt2::meta::call<frexp_(vT)>::type)
                  , (std::pair<vT,viT>)
                  );

  {
    viT e;
    vT  m;

    frexp(nt2::One<vT>(), m, e);
    NT2_TEST_EQUAL(m, nt2::Half<vT>());
    NT2_TEST_EQUAL(e, nt2::One<viT>());
  }

  {
    viT e;
    vT  m;

    m = frexp(nt2::One<vT>(), e);
    NT2_TEST_EQUAL(m, nt2::Half<vT>());
    NT2_TEST_EQUAL(e, nt2::One<viT>());
  }

  {
    viT e;
    vT  m;

    boost::fusion::vector_tie(m,e) = frexp(nt2::One<vT>());
    NT2_TEST_EQUAL(m, nt2::Half<vT>());
    NT2_TEST_EQUAL(e, nt2::One<viT>());
  }

  {
    std::pair<vT,viT> p;

    p = frexp(nt2::One<vT>());
    NT2_TEST_EQUAL(p.first  , nt2::Half<vT>());
    NT2_TEST_EQUAL(p.second , nt2::One<viT>());
  }
}
