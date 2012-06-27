//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - cauchy function"

#include <nt2/table.hpp>
#include <nt2/include/functions/cauchy.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( cauchy_ints, NT2_REAL_TYPES)
{
  //  nt2::display("cauchy(3, 4, nt2::meta::as_<T>())", nt2::cauchy(3, 4, nt2::meta::as_<T>()));
  nt2::table<T> a0 = nt2::_(T(1), 4); 
  nt2::display("cauchy(a0)", nt2::cauchy(a0));
  nt2::table<T> v =  cauchy(a0);
  nt2::display("v", v);
 
  T res[16] = {  0.500000000000000 ,   0.333333333333333,    0.250000000000000,    0.200000000000000, 
                 0.333333333333333,    0.250000000000000,    0.200000000000000,    0.166666666666667, 
                 0.250000000000000,    0.200000000000000,    0.166666666666667,    0.142857142857143, 
                 0.200000000000000,    0.166666666666667,    0.142857142857143,    0.125000000000000}; 
  int k = 0; 
 for(int i=1; i <= 4; i++)
   {
     for(int j=1; j <= 4; j++)
       {
         NT2_TEST_EQUAL(res[k], v(i, j));
         k++; 
       }
   }
}

