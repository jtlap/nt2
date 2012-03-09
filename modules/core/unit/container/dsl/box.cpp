/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container box"

#include <nt2/sdk/meta/as.hpp>
#include <nt2/include/functions/box.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

struct foo { int i; };

NT2_TEST_CASE( arity_of )
{
  using nt2::box;
  using nt2::_2D;
  using boost::mpl::_;
  using nt2::tag::box_;
  using nt2::meta::as_;
  using boost::proto::arity_of;

  box < foo         > a0;
  box < as_<float>  > a1;
  box < _2D         > a2;

  NT2_TEST_EXPR_TYPE( a0, arity_of<_>, (boost::mpl::long_<0l>) );
  NT2_TEST_EXPR_TYPE( a1, arity_of<_>, (boost::mpl::long_<0l>) );
  NT2_TEST_EXPR_TYPE( a2, arity_of<_>, (boost::mpl::long_<0l>) );
}

NT2_TEST_CASE( semantic_of )
{
  using nt2::box;
  using nt2::_2D;
  using boost::mpl::_;
  using nt2::tag::box_;
  using nt2::meta::as_;
  using boost::dispatch::meta::semantic_of;

  box < foo         > a0;
  box < as_<float>  > a1;
  box < _2D         > a2;

  NT2_TEST_EXPR_TYPE( a0, semantic_of<_>, (foo) );
  NT2_TEST_EXPR_TYPE( a1, semantic_of<_>, (as_<float>) );
  NT2_TEST_EXPR_TYPE( a2, semantic_of<_>, (_2D) );
}

NT2_TEST_CASE( value_semantic )
{
  using nt2::box;
  using nt2::tag::box_;

  foo f = { 42 };

  box < foo > a0(f);
  NT2_TEST_EQUAL( f.i, a0.value().i );

  f.i = 66;
  NT2_TEST_EQUAL( a0.value().i, 42 );

  a0 = f;
  NT2_TEST_EQUAL( f.i, a0.value().i );
}

// For the sake of it, let's pretend foo can do plus
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION
  ( boost::simd::tag::plus_, tag::cpu_, (A0)
  , (unspecified_< const foo >)(unspecified_<A0>)
  )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2) { return a0; }
  };
} } }

foo make_foo(int i) { foo f = {i}; return f; }

NT2_TEST_CASE( temp_semantic )
{
  using nt2::box;
  using nt2::boxify;
  using nt2::tag::box_;

  box < foo > a0(make_foo(42));
  NT2_TEST_EQUAL( 42, a0.value().i );

  BOOST_AUTO(temporary_boxes, boxify( make_foo(42) ) + boxify( make_foo(24) ) );

  NT2_TEST_EQUAL( 42, boost::proto::child_c<0>( temporary_boxes).value().i );
  NT2_TEST_EQUAL( 24, boost::proto::child_c<1>( temporary_boxes ).value().i );
}
