//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/rem_pio2_medium.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/pio_4.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL ( rem_pio2_medium_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::rem_pio2_medium;
  using nt2::tag::rem_pio2_medium_;
  using boost::simd::native;
  typedef typename nt2::meta::as_integer<T>::type           iT;
  typedef native<T,BOOST_SIMD_DEFAULT_EXTENSION>            vT;
  typedef native<iT,BOOST_SIMD_DEFAULT_EXTENSION>          viT;

  {
    vT r1;
    NT2_TEST_EQUAL( rem_pio2_medium(nt2::Pio_2<vT>(), r1), nt2::One<viT>());
    NT2_TEST_ULP_EQUAL( r1, nt2::Zero<vT>(), 0.5);
    NT2_TEST_EQUAL( rem_pio2_medium(nt2::Pio_4<vT>()*nt2::Half<T>(), r1), nt2::Zero<viT>());
    NT2_TEST_ULP_EQUAL( r1, nt2::Pio_4<vT>()*nt2::Half<vT>(), 0.5);
  }

}
