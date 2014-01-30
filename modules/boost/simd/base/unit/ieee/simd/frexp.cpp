//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/frexp.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/half.hpp>
#include <boost/simd/include/constants/limitexponent.hpp>
#include <boost/simd/include/constants/mindenormal.hpp>
#include <boost/simd/include/constants/minexponent.hpp>
#include <boost/simd/include/constants/halfeps.hpp>
#include <boost/simd/include/constants/nbmantissabits.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/two.hpp>
#include <boost/simd/include/constants/four.hpp>
#include <boost/simd/include/functions/divides.hpp>
#include <boost/simd/include/functions/ldexp.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( frexp0, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::frexp;
  using boost::simd::ldexp;
  using boost::simd::tag::frexp_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  typedef typename boost::dispatch::meta::as_integer<vT,signed>::type viT;

  {
    viT e;
    vT  m;
    vT  a = boost::simd::Valmax<vT>();
    frexp(a, m, e);
    NT2_TEST_ULP_EQUAL(m, boost::simd::One<vT>()-boost::simd::Halfeps<vT>(), 1);
    NT2_TEST_EQUAL(e, boost::simd::Limitexponent<vT>());
    NT2_TEST_EQUAL(ldexp(m,e),a);
  }
#ifndef BOOST_SIMD_NO_DENORMALS
  {
    viT e;
    vT  m;
    vT  a = boost::simd::Mindenormal<vT>();
    frexp(a, m, e);
    NT2_TEST_ULP_EQUAL(m, boost::simd::Half<vT>(), 1);
    NT2_TEST_EQUAL(e, boost::simd::Minexponent<vT>()-boost::simd::Nbmantissabits<vT>()+boost::simd::One<viT>());
    NT2_TEST_EQUAL(ldexp(m,e),a);
 }

  {
    viT e;
    vT  m;
    vT  a = boost::simd::Smallestposval<vT>()/boost::simd::Two<vT>();
    frexp(a, m, e);
    NT2_TEST_ULP_EQUAL(m, boost::simd::Half<vT>(), 1);
    NT2_TEST_EQUAL(e, boost::simd::Minexponent<vT>());
    NT2_TEST_EQUAL(ldexp(m,e),a);
 }

  {
    viT e;
    vT  m;
    vT  a = boost::simd::Smallestposval<vT>()/boost::simd::Four<vT>();
    frexp(a, m, e);
    NT2_TEST_ULP_EQUAL(m, boost::simd::Half<vT>(), 1);
    NT2_TEST_EQUAL(e, boost::simd::Minexponent<vT>()-boost::simd::One<viT>());
    NT2_TEST_EQUAL(ldexp(m,e),a);
 }
#endif
}

NT2_TEST_CASE_TPL( frexp, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::frexp;
  using boost::simd::tag::frexp_;
  using boost::simd::native;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  typedef typename boost::dispatch::meta::as_integer<vT,signed>::type viT;

  NT2_TEST_TYPE_IS( (typename boost::dispatch::meta::call<frexp_(vT)>::type)
                  , (std::pair<vT,viT>)
                  );

  {
    viT e;
    vT  m;

    frexp(boost::simd::One<vT>(), m, e);
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<viT>());
  }

  {
    viT e;
    vT  m;

    m = frexp(boost::simd::One<vT>(), e);
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<viT>());
  }

  {
    viT e;
    vT  m;

    boost::fusion::vector_tie(m,e) = frexp(boost::simd::One<vT>());
    NT2_TEST_EQUAL(m, boost::simd::Half<vT>());
    NT2_TEST_EQUAL(e, boost::simd::One<viT>());
  }

  {
    std::pair<vT,viT> p;

    p = frexp(boost::simd::One<vT>());
    NT2_TEST_EQUAL(p.first  , boost::simd::Half<vT>());
    NT2_TEST_EQUAL(p.second , boost::simd::One<viT>());
  }
}
