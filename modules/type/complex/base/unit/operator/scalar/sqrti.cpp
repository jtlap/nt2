//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/constants/sqrti.hpp>

#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <complex>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>

#include <nt2/include/constants/sqrt_2.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>

NT2_TEST_CASE_TPL ( sqrti_real,  BOOST_SIMD_REAL_TYPES)
{
  typedef typename std::complex<T> cT;

  // specific values tests
  NT2_TEST_EQUAL(nt2::Sqrti<cT>(),  cT(nt2::Sqrt_2o_2<T>(),nt2::Sqrt_2o_2<T>()));
}
