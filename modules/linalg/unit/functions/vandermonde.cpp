//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - vandermonde function"

#include <nt2/table.hpp>
#include <nt2/include/functions/vandermonde.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( vandermonde_ints, NT2_REAL_TYPES)
{
  nt2::table<T> a0 = nt2::_(T(1), 3);
  nt2::table<T> v  =  nt2::vandermonde(a0); 
  nt2::display("vandermonde(a0)", v);
  nt2::display("vandermonde(a0)", nt2::vandermonde(a0)); 
}

