//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 function tie"

#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/fusion/include/vector.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE( extent )
{
  using nt2::table;
  using nt2::of_size_;
  using boost::mpl::_;

  table<double> d;
  table<float>  f;
  table<short>  s;
  table<char>   c;

  NT2_TEST_EQUAL( nt2::tie(d).extent()       , d.extent() );
  NT2_TEST_EQUAL( nt2::tie(f,d).extent()     , f.extent() );
  NT2_TEST_EQUAL( nt2::tie(f,d,s).extent()   , f.extent() );
  NT2_TEST_EQUAL( nt2::tie(c,f,d,s).extent() , c.extent() );
}

template<class Expr>
void meta_impl(Expr const&)
{
  typedef std::complex<float> cT;
  typedef nt2::container::composite_reference<cT> cTref;

  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::scalar_of<Expr>::type, (boost::fusion::vector2< cTref, cT >));
  NT2_TEST_TYPE_IS(typename boost::dispatch::meta::primitive_of<Expr>::type, (boost::fusion::vector2<float&, float>));
  NT2_TEST_TYPE_IS(typename Expr::value_type, (boost::fusion::vector2<cT, cT>));
}

NT2_TEST_CASE( meta )
{
  using nt2::table;
  table< std::complex<float>, nt2::deinterleaved_ > a, b, c, d;

  meta_impl(nt2::tie(a, b + c));
}

NT2_TEST_CASE( loop_fusion )
{
  using nt2::table;
  using nt2::cons;

  table<float> a, b, c, d;
  a = nt2::colvect(nt2::_(1.f, 10));
  b = nt2::colvect(nt2::_(11.f, 20));

  nt2::tie(c, d) = nt2::tie(a + b, a - b);
  NT2_TEST_EQUAL(c, cons<float>(12, 14, 16, 18, 20, 22, 24, 26, 28, 30));
  NT2_TEST_EQUAL(d, cons<float>(-10, -10, -10, -10, -10, -10, -10, -10, -10, -10));
}
