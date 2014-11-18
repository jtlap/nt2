//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/swar/include/functions/split.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( split, BOOST_SIMD_SIMD_SPLITABLE_TYPES )
{
  using nt2::splat;
  using nt2::split;
  using nt2::tag::split_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             vT;

  typedef typename boost::dispatch::meta::upgrade<vT>::type uvT;

  {
    uvT f,s;

    split(nt2::Valmax<vT>(), f, s);
    NT2_TEST_EQUAL(f, nt2::splat<uvT>(nt2::Valmax<T>()) );
    NT2_TEST_EQUAL(s, nt2::splat<uvT>(nt2::Valmax<T>()) );

    split(nt2::Valmin<vT>(), f, s);
    NT2_TEST_EQUAL(f, nt2::splat<uvT>(nt2::Valmin<T>()) );
    NT2_TEST_EQUAL(s, nt2::splat<uvT>(nt2::Valmin<T>()) );
  }

  {
    uvT f,s;

    f = split(nt2::Valmax<vT>(), s);
    NT2_TEST_EQUAL(f, nt2::splat<uvT>(nt2::Valmax<T>()) );
    NT2_TEST_EQUAL(s, nt2::splat<uvT>(nt2::Valmax<T>()) );

    f = split(nt2::Valmin<vT>(), s);
    NT2_TEST_EQUAL(f, nt2::splat<uvT>(nt2::Valmin<T>()) );
    NT2_TEST_EQUAL(s, nt2::splat<uvT>(nt2::Valmin<T>()) );
  }
}

NT2_TEST_CASE_TPL( split_one_output, BOOST_SIMD_SIMD_TYPES )
{
  using nt2::splat;
  using nt2::split;
  using nt2::tag::split_;
  using boost::simd::native;

  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>             vT;


  typedef typename boost::simd::meta::
          vector_of< typename boost::dispatch::meta::
                     upgrade<T>::type
                   , vT::static_size
                   >::type uvT2;

  NT2_TEST_TYPE_IS( (typename nt2::meta::call<split_(vT)>::type)
                  , uvT2
                  );

  {
    uvT2 p;

    p = split(nt2::Valmax<vT>());
    NT2_TEST_EQUAL(p, nt2::splat<uvT2>(nt2::Valmax<T>()) );

    p = split(nt2::Valmin<vT>());
    NT2_TEST_EQUAL(p, nt2::splat<uvT2>(nt2::Valmin<T>()) );
  }
}
