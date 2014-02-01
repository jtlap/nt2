//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/rem_pio2.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/include/constants/pio_4.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/aligned_load.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( rem_pio2_real__1_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::rem_pio2;
  using nt2::tag::rem_pio2_;
  using nt2::aligned_load;
  using boost::simd::native;
  using nt2::meta::cardinal_of;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                vT;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef native<iT,ext_t>                       ivT;
  typedef typename nt2::meta::call<rem_pio2_(vT)>::type r_t;

  r_t r = nt2::rem_pio2(nt2::Zero<vT>());
  NT2_TEST_EQUAL(boost::fusion::get<0>(r), nt2::Zero<ivT>());
  NT2_TEST_EQUAL(boost::fusion::get<1>(r), nt2::Zero<vT>());
  NT2_TEST_EQUAL(boost::fusion::get<2>(r), nt2::Zero<vT>());
 } // end of test for floating_
