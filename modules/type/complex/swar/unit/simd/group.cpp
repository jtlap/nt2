 //==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 swar toolbox - group/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of swar components in simd mode
//////////////////////////////////////////////////////////////////////////////

#include <nt2/swar/include/functions/group.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( group_complex,  BOOST_SIMD_SIMD_REAL_GROUPABLE_TYPES)
{
  using nt2::group;
  using nt2::tag::group_;
  using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION                    ext_t;
  typedef native<T,ext_t>                                  vT;
  typedef typename nt2::meta::as_complex<vT>::type        cvT;
  typedef typename nt2::meta::call<group_(cvT,cvT)>::type r_t;
  typedef typename nt2::meta::downgrade<cvT>::type   wished_t;

  NT2_TEST_TYPE_IS(r_t, wished_t);

  NT2_TEST_EQUAL(group(nt2::One<cvT>(), nt2::One<cvT>()),   nt2::One<r_t>());
  NT2_TEST_EQUAL(group(nt2::Zero<cvT>(), nt2::Zero<cvT>()), nt2::Zero<r_t>());
}

NT2_TEST_CASE( dummy_for_altivec )
{
  NT2_TEST_COMPLETE("dummy for altivec and similar extensions");
}
