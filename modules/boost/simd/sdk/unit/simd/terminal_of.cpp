/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::meta::terminal_of SIMD"

#include <boost/mpl/apply.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/toolbox/operator.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/details/decltype.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test that terminal_of on SIMD expression
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(terminal_of_pack, BOOST_SIMD_TYPES)
{
  using boost::simd::pack;
  using boost::dispatch::meta::terminal_of;
  using boost::is_same;

  BOOST_DISPATCH_DECLTYPE(pack<T>() + pack<T>()+3, expr);
  NT2_TEST( (is_same<typename boost::mpl::apply<terminal_of< pack<T> >, void >::type, pack<T> >::value) );
  NT2_TEST( (is_same<typename boost::mpl::apply<terminal_of< expr    >, void >::type, pack<T> >::value) );
  typedef pack<T,1>   native1_t;
  typedef pack<T,2>   native2_t;
  typedef pack<T,4>   native4_t;
  typedef pack<T,8>   native8_t;
  typedef pack<T,16>  native16_t;

  native2_t n,p,q;
  p.fill(2);
  q.fill(4);
  //n = p+q;

  //  NT2_TEST( (is_same<typename terminal_of< native1_t >::type, native1_t >::value)  );
  //NT2_TEST( (is_same<typename terminal_of< native2_t >::type, native2_t >::value)  );
  //NT2_TEST( (is_same<typename terminal_of< native4_t >::type, native4_t >::value)  );
  //NT2_TEST( (is_same<typename terminal_of< native8_t >::type, native8_t >::value)  );
  //NT2_TEST( (is_same<typename terminal_of< native16_t>::type, native16_t >::value) );

}

