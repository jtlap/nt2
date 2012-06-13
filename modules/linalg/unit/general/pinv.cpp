//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - pinv factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/pinv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(pinv, NT2_REAL_TYPES)
{
  typedef T r_t; 
  using nt2::pinv; 
  using nt2::tag::pinv_;
  using nt2::mtimes; 
  {
    nt2::table<T> n = nt2::eye(3, 3, nt2::meta::as_<T>()), n1, p;
    n1 = n; 
    n1(nt2::_, 1) = T(0.5); 
    nt2::table<T> pinvn1 = nt2::pinv(n1, nt2::Eps<T>());
    NT2_DISP(n1); 
    NT2_DISP(pinvn1);
    p = mtimes(n1, pinvn1); 
    NT2_DISP(p); 
    for(int i=1; i <= 3; i++)
      {
        NT2_TEST_ULP_EQUAL(p(i),n(i), 20);
      }
  }
  {
    nt2::table<T> n = nt2::eye(3, 3, nt2::meta::as_<T>()), n1, p;
    n1 = n; 
    n1(nt2::_, 1) = T(0.5); 
    nt2::table<T> pinvn1 = nt2::pinv(n1);
    NT2_DISP(n1); 
    NT2_DISP(pinvn1);
    p = mtimes(n1, pinvn1); 
    NT2_DISP(p); 
    for(int i=1; i <= 3; i++)
      {
        NT2_TEST_ULP_EQUAL(p(i),n(i), 20);
      }
  }
 }
