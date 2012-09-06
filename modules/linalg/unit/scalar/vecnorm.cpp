//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - vecnorm factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/vecnorm.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/pow.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/minf.hpp>   

#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(vecnorm, NT2_REAL_TYPES)
{
  typedef T r_t; 
  using nt2::vecnorm; 
  using nt2::tag::vecnorm_;
  nt2::table<T> n = nt2::ones(10, 1, nt2::meta::as_<T>()); 
  NT2_TEST_ULP_EQUAL(vecnorm(n, 1), nt2::Ten<T>(), 0);
  NT2_TEST_ULP_EQUAL(vecnorm(n, 2), nt2::sqrt(nt2::Ten<T>()), 0);
  NT2_TEST_ULP_EQUAL(vecnorm(n)   , nt2::sqrt(nt2::Ten<T>()), 0);  
  NT2_TEST_ULP_EQUAL(vecnorm(n, 3), nt2::pow(nt2::Ten<T>(), 1/T(3)), 0); 
  NT2_TEST_ULP_EQUAL(vecnorm(n, nt2::Inf<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(vecnorm(n, nt2::Minf<T>()), nt2::One<T>(), 0);                     
}
