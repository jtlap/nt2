/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::meta::terminal_of SIMD"

#include <boost/mpl/apply.hpp>
#include <nt2/sdk/simd/pack.hpp>
#include <nt2/toolbox/operator.hpp>
#include <boost/type_traits/is_same.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that terminal_of on SIMD expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(terminal_of_pack, NT2_SIMD_TYPES)
{
  using nt2::simd::pack;
  using nt2::meta::terminal_of;
  using boost::is_same;

  NT2_DECLTYPE(pack<T>() + pack<T>()+3, expr);
  NT2_TEST( (is_same<typename boost::mpl::apply<terminal_of< pack<T> >, void >::type, pack<T> >::value) );
  NT2_TEST( (is_same<typename boost::mpl::apply<terminal_of< expr    >, void >::type, pack<T> >::value) );
}
