//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::complex hierarchy"

#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/imaginary.hpp>
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

NT2_TEST_CASE(imaginary_hierarchy)
{
  using namespace boost::dispatch::meta;
  using nt2::imaginary;
  
  imaginary<double> im;
  
  NT2_TEST_EXPR_TYPE(im, hierarchy<0>, scalar_< imaginary_< double_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<1>, scalar_< imaginary_< type64_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<2>, scalar_< imaginary_< floating_sized_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<3>, scalar_< imaginary_< floating_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<4>, scalar_< imaginary_< signed_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<5>, scalar_< imaginary_< arithmetic_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<6>, scalar_< imaginary_< fundamental_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<7>, scalar_< imaginary_< unspecified_< imaginary<double> > > >);
  NT2_TEST_EXPR_TYPE(im, hierarchy<8>, scalar_< complex_< double_< imaginary<double> > > >);
}

NT2_TEST_CASE(imaginary_hierarchy_simd)
{
  using namespace boost::dispatch::meta;
  using nt2::imaginary;
  using boost::simd::native;
  
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;
  
  native<imaginary<double>, ext_t> im;
  
  NT2_TEST_EXPR_TYPE(im, hierarchy<0>, (simd_< imaginary_< double_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<1>, (simd_< imaginary_< type64_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<2>, (simd_< imaginary_< floating_sized_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<3>, (simd_< imaginary_< floating_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<4>, (simd_< imaginary_< signed_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<5>, (simd_< imaginary_< arithmetic_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<6>, (simd_< imaginary_< fundamental_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<7>, (simd_< imaginary_< unspecified_< native<imaginary<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<8>, (simd_< complex_< double_< native<imaginary<double>, ext_t> > >, ext_t >));
}

NT2_TEST_CASE(complex_hierarchy)
{
  using namespace boost::dispatch::meta;
  using std::complex;
  
  complex<double> c;
  
  NT2_TEST_EXPR_TYPE(c, hierarchy<0>, scalar_< complex_< double_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<1>, scalar_< complex_< type64_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<2>, scalar_< complex_< floating_sized_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<3>, scalar_< complex_< floating_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<4>, scalar_< complex_< signed_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<5>, scalar_< complex_< arithmetic_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<6>, scalar_< complex_< fundamental_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<7>, scalar_< complex_< unspecified_< complex<double> > > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<8>, scalar_< unspecified_< complex<double> > >);
  NT2_TEST_EXPR_TYPE(c, hierarchy<9>, generic_< complex_< double_< complex<double> > > >);
}

NT2_TEST_CASE(complex_hierarchy_simd)
{
  using namespace boost::dispatch::meta;
  using std::complex;
  using boost::simd::composite;
  
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;
  
  composite<complex<double>, ext_t> im;
  
  NT2_TEST_EXPR_TYPE(im, hierarchy<0>, (simd_< complex_< double_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<1>, (simd_< complex_< type64_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<2>, (simd_< complex_< floating_sized_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<3>, (simd_< complex_< floating_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<4>, (simd_< complex_< signed_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<5>, (simd_< complex_< arithmetic_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<6>, (simd_< complex_< fundamental_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<7>, (simd_< complex_< unspecified_< composite<complex<double>, ext_t> > >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<8>, (simd_< unspecified_< composite<complex<double>, ext_t> >, ext_t >));
  NT2_TEST_EXPR_TYPE(im, hierarchy<9>, (generic_< complex_< double_< composite<complex<double>, ext_t> > > >));
}
