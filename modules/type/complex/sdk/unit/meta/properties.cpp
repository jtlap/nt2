//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::complex properties"

#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/real_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <iostream>

NT2_TEST_CASE(properties)
{
  using namespace nt2::meta;
  using std::complex;
  using boost::mpl::_;
  using boost::simd::logical;

  complex<float> c;
  NT2_TEST_EXPR_TYPE(c, scalar_of<_>, complex<float>);
  NT2_TEST_EXPR_TYPE(c, real_of<_>, float);
  NT2_TEST_EXPR_TYPE(c, as_real<_>, float);
  NT2_TEST_EXPR_TYPE(c, as_complex<_>, complex<float>);
  NT2_TEST_EXPR_TYPE(c, as_logical<_>, logical<float>);
}

NT2_TEST_CASE(properties_simd)
{
  using namespace nt2::meta;
  using namespace boost::simd::meta;
  using std::complex;
  using boost::mpl::_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

  native<complex<float>, ext_t> c;
  NT2_TEST_EXPR_TYPE(c, scalar_of<_>, complex<float>);
  NT2_TEST_EXPR_TYPE(c, real_of<_>, float);
  NT2_TEST_EXPR_TYPE(c, as_real<_>, (native<float, ext_t>));
  NT2_TEST_EXPR_TYPE(c, as_complex<_>, (native<complex<float>, ext_t>));
  NT2_TEST_EXPR_TYPE(c, as_logical<_>, (native<logical<float>, ext_t>));
}
