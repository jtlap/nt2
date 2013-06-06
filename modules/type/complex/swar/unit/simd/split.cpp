//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/swar/include/functions/split.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/sdk/meta/type_id.hpp>

#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( split_complex, BOOST_SIMD_REAL_SPLITABLE_TYPES )
{
  using nt2::split;
  using nt2::tag::split_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION                    ext_t;
  typedef native<T,ext_t>                                  vT;
  typedef typename nt2::meta::as_complex<vT>::type        cvT;

  typedef typename boost::dispatch::meta::upgrade<vT>::type uvT;
  typedef typename nt2::meta::as_complex<uvT>::type        ucvT;
  typedef typename nt2::meta::call<split_(cvT)>::type  wished_t;

  NT2_TEST_TYPE_IS( (wished_t)
                  , (std::pair<ucvT,ucvT>)
                  );

  {
    std::cout << nt2::type_id<ucvT>() << std::endl;
    std::cout << nt2::type_id<std::pair<ucvT,ucvT> >() << std::endl;
    std::cout << nt2::type_id<std::pair<ucvT,ucvT> >() << std::endl;
    ucvT f,s;

    split(nt2::One<cvT>(), f, s);
    NT2_TEST_EQUAL(f, nt2::One<ucvT>() );
    NT2_TEST_EQUAL(s, nt2::One<ucvT>() );

    split(nt2::Zero<cvT>(), f, s);
    NT2_TEST_EQUAL(f, nt2::Zero<ucvT>() );
    NT2_TEST_EQUAL(s, nt2::Zero<ucvT>() );
  }

  {
    ucvT f,s;

    f = split(nt2::One<cvT>(), s);
    NT2_TEST_EQUAL(f, nt2::One<ucvT>() );
    NT2_TEST_EQUAL(s, nt2::One<ucvT>() );

    f = split(nt2::Zero<cvT>(), s);
    NT2_TEST_EQUAL(f, nt2::Zero<ucvT>() );
    NT2_TEST_EQUAL(s, nt2::Zero<ucvT>() );
  }

  {
    std::pair<ucvT, ucvT> p;
    p = split(nt2::Zero<cvT>());

    NT2_TEST_EQUAL(p.first, nt2::Zero<ucvT>() );
    NT2_TEST_EQUAL(p.second, nt2::Zero<ucvT>() );

    p = split(nt2::One<cvT>());

    NT2_TEST_EQUAL(p.first, nt2::One<ucvT>() );
    NT2_TEST_EQUAL(p.second, nt2::One<ucvT>() );
  }

}

