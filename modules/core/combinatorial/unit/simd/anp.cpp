//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/combinatorial/include/functions/anp.hpp>

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE_TPL ( anp_real,  NT2_SIMD_REAL_TYPES)
{
  using nt2::anp;
  using nt2::tag::anp_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;


  // specific values tests
#ifndef BOOST_SIMD_NO_INVALIDS
  NT2_TEST_EQUAL(anp(nt2::Inf<vT>(), nt2::Inf<vT>()), nt2::Nan<vT>());
  NT2_TEST_EQUAL(anp(nt2::Nan<vT>(), nt2::Nan<vT>()), nt2::Nan<vT>());
#endif
  NT2_TEST_EQUAL(anp(nt2::One<vT>(), nt2::One<vT>()), nt2::One<vT>());
  NT2_TEST_EQUAL(anp(nt2::Zero<vT>(), nt2::Zero<vT>()), nt2::One<vT>());
}
