//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 operator toolbox - map/simd Mode"

#include <nt2/toolbox/operator/include/functions/map.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>
#include <nt2/include/functions/unary_plus.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/allbits.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( map_integer__2_0,  BOOST_SIMD_SIMD_TYPES)
{
  using nt2::map;
  using boost::simd::native;
  using nt2::tag::map_;
  using nt2::tag::unary_plus_;
  using nt2::tag::plus_;
  using nt2::tag::if_else_;
  typedef boost::dispatch::functor<unary_plus_> uni_f;
  typedef boost::dispatch::functor<plus_> bin_f;
  typedef boost::dispatch::functor<if_else_> tri_f;

  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION> nT;

  typedef typename boost::dispatch::meta::call<map_(uni_f,nT)>::type ur_t;
  typedef typename boost::dispatch::meta::call<map_(bin_f,nT,nT)>::type br_t;
  typedef typename boost::dispatch::meta::call<map_(tri_f,nT,nT,nT)>::type tr_t;

  // return type conformity test
  NT2_TEST_TYPE_IS(ur_t, nT);
  NT2_TEST_TYPE_IS(br_t, nT);
  NT2_TEST_TYPE_IS(tr_t, nT);

  // specific values tests
  NT2_TEST_EQUAL(map(uni_f(), nt2::One<nT>()), nt2::One<ur_t>());
  NT2_TEST_EQUAL(map(uni_f(), nt2::One<nT>()), nt2::One<ur_t>());
  NT2_TEST_EQUAL(map(uni_f(), nt2::One<nT>()), nt2::One<ur_t>());

  NT2_TEST_EQUAL(map(bin_f(), nt2::One<nT>(), nt2::One<nT>()), nt2::Two<br_t>());
  NT2_TEST_EQUAL(map(bin_f(), nt2::One<nT>(), nt2::One<nT>()), nt2::Two<br_t>());
  NT2_TEST_EQUAL(map(bin_f(), nt2::One<nT>(), nt2::One<nT>()), nt2::Two<br_t>());

  NT2_TEST_EQUAL(map(tri_f(), nt2::Zero<nT>(),nt2::One<nT>(), nt2::Two<nT>()), nt2::Two<br_t>());
  NT2_TEST_EQUAL(map(tri_f(), nt2::One<nT>(), nt2::One<nT>(), nt2::Two<nT>()), nt2::One<br_t>());
}

struct logical_f
{
  template<class Sig>
  struct result;

  template<class This, class A0>
  struct result<This(A0)>
  {
    typedef typename boost::dispatch::meta::strip<A0>::type A0_;
    typedef typename boost::simd::meta::as_logical<A0_>::type type;
  };

  template<class A0>
  typename result<logical_f(A0 const&)>::type operator()(A0 const& a0) const
  {
    return boost::simd::logical<A0>(true);
  }

  template<class A0, class X>
  typename result<logical_f(boost::simd::native<A0, X> const&)>::type operator()(boost::simd::native<A0, X> const& a0) const
  {
    return boost::simd::map(*this, a0);
  }
};

NT2_TEST_CASE_TPL ( map_logical, (float)(nt2::int32_t)(nt2::uint32_t) )
{
  using boost::simd::logical;
  using boost::simd::native;
  using boost::simd::map;
  using boost::simd::bitwise_cast;
  using boost::simd::Allbits;
  using boost::mpl::_;
  typedef native<T, BOOST_SIMD_DEFAULT_EXTENSION> in_type;
  typedef native<logical<T>, BOOST_SIMD_DEFAULT_EXTENSION> out_type;
  typedef native<typename boost::dispatch::meta::as_integer<T, unsigned>::type, BOOST_SIMD_DEFAULT_EXTENSION> mask_type;

  in_type a;
  NT2_TEST_EXPR_TYPE( map(logical_f(), a), _, out_type );
  NT2_TEST_EQUAL( bitwise_cast<mask_type>( map(logical_f(), a) ), Allbits<mask_type>() );
}
