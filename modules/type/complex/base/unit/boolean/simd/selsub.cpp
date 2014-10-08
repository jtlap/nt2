//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/selsub.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/mtwo.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/zero.hpp>

NT2_TEST_CASE_TPL( selsub_floating, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using nt2::selsub;
  using nt2::tag::selsub_;
  typedef typename std::complex<T> cT;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<cT,ext_t>                vcT;

  // specific values tests
  NT2_TEST_EQUAL(selsub(nt2::One<vcT>(), nt2::Mone<vcT>()   , nt2::One<vcT>()   ), nt2::Mtwo<vcT>());
  NT2_TEST_EQUAL(selsub(nt2::One<vcT>(), nt2::One<vcT>()    , nt2::One<vcT>()    ), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(selsub(nt2::One<vcT>(), nt2::Valmax<vcT>() , nt2::One<vcT>() ), nt2::Valmax<vcT>());
  NT2_TEST_EQUAL(selsub(nt2::One<vcT>(), nt2::Zero<vcT>()   , nt2::One<vcT>()   ), nt2::Mone<vcT>());
  NT2_TEST_EQUAL(selsub(nt2::Zero<vcT>(), nt2::Mone<vcT>()  , nt2::One<vcT>()  ), nt2::Mone<vcT>());
  NT2_TEST_EQUAL(selsub(nt2::Zero<vcT>(), nt2::Zero<vcT>()  , nt2::One<vcT>()  ), nt2::Zero<vcT>());
  NT2_TEST_EQUAL(selsub(nt2::Zero<vcT>(), nt2::Valmax<vcT>(), nt2::One<vcT>()), nt2::Valmax<vcT>());
  NT2_TEST_EQUAL(selsub(nt2::Zero<vcT>(), nt2::Zero<vcT>()  , nt2::One<vcT>()  ), nt2::Zero<vcT>());
}
