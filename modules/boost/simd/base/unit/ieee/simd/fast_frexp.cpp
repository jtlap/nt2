//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/fast_frexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL( fast_frexp,  NT2_REAL_TYPES)
{
  using boost::simd::fast_frexp;
  using boost::simd::tag::fast_frexp_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<fast_frexp_(vT)>::type)
                  , (std::pair<vT,ivT>)
                  );

  {
    ivT e;
    vT  m;

    fast_frexp(boost::simd::One<vT>(), m, e);
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<ivT>());
  }

  {
    ivT e;
    vT  m;

    m = fast_frexp(boost::simd::One<vT>(), e);
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<ivT>());
  }

  {
    ivT e;
    vT  m;

    boost::fusion::vector_tie(m,e) = fast_frexp(boost::simd::One<vT>());
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<ivT>());
  }

  {
    std::pair<vT,ivT> p;

    p = fast_frexp(boost::simd::One<vT>());
    NT2_TEST_EQUAL(p.first  , boost::simd::Half<vT>());
    NT2_TEST_EQUAL(p.second , boost::simd::One<ivT>());
  }
}
