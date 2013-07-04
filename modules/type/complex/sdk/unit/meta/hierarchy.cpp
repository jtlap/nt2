//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/complex/complex.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <iostream>

template<int N>
struct hierarchy;

template<>
struct hierarchy<0>
{
  template<class X>
  struct apply
    : boost::dispatch::meta::hierarchy_of<X>
  {
  };
};

template<int N>
struct hierarchy
{
  template<class X>
  struct apply
  {
    typedef typename hierarchy<N-1>::template apply<X>::type::parent type;
  };
};

NT2_TEST_CASE(complex_hierarchy)
{
  using namespace boost::dispatch::meta;
  using std::complex;

  complex<float> c;

  NT2_TEST_EXPR_TYPE(c, hierarchy<0>, scalar_< complex_< single_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<1>, scalar_< complex_< type32_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<2>, scalar_< complex_< floating_sized_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<3>, scalar_< complex_< floating_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<4>, scalar_< complex_< signed_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<5>, scalar_< complex_< arithmetic_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<6>, scalar_< complex_< fundamental_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<7>, scalar_< complex_< unspecified_< complex<float> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<8>, scalar_< fusion_sequence_< complex<float> > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<9>, scalar_< unspecified_< complex<float> > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<10>, generic_< complex_< single_< complex<float> > > >);
}

NT2_TEST_CASE(complex_hierarchy_simd)
{
  using namespace boost::dispatch::meta;
  using std::complex;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  native<complex<float>, ext_t> im;

  NT2_TEST_EXPR_TYPE(im, hierarchy<0>, (simd_< complex_< single_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<1>, (simd_< complex_< type32_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<2>, (simd_< complex_< floating_sized_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<3>, (simd_< complex_< floating_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<4>, (simd_< complex_< signed_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<5>, (simd_< complex_< arithmetic_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<6>, (simd_< complex_< fundamental_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<7>, (simd_< complex_< unspecified_< native<complex<float>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<8>, (simd_< fusion_sequence_< native<complex<float>, ext_t> >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<9>, (simd_< unspecified_< native<complex<float>, ext_t> >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<10>, (generic_< complex_< single_< native<complex<float>, ext_t> > > >));
}
