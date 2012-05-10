//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - null space"

#include <nt2/table.hpp>
#include <nt2/include/functions/null.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(null, NT2_REAL_TYPES)
{
  typedef T r_t; 
  using nt2::null; 
  using nt2::tag::null_;
  double ulpd =  0.0; 
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  n(3, 5) = T(2);
  n(4, 4) = T(0);
  n(1, 1) = 5*nt2::Eps<T>(); 
  nt2::table<T> nulln = nt2::null(n);
  NT2_DISP(n); 
  NT2_DISP(nulln); 
  nt2::table<T> nulln1 = nt2::null(n,  100*nt2::Eps<T>());
  NT2_DISP(nulln1); 

 }
