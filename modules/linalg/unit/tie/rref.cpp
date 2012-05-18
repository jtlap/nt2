//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied rref function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/rref.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( rref, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_integer<T, signed>::type  itype_t;
  typedef nt2::table<itype_t> it_t; 
  typedef nt2::table<T> table_t;
  T A[16] = { 
   16,    2,    3,   13, 
    5,   11,   10,    8, 
    9,    7,    6,   12, 
   4,   14,   15,    1}; 
  table_t b = nt2::ones(4, 4, nt2::meta::as_<T>())
                + T(10)*nt2::eye(4, 4, nt2::meta::as_<T>());
  table_t rref, l, u, p; 
  table_t a(nt2::of_size(4, 4));
  int k = 0; 
  for(int i=1; i <= 4; ++i)
    {
      for(int j=1; j <= 4; ++j)
        {
          a(i, j) = A[k++]; 
        }
    }

  nt2::tie(rref) = nt2::rref(b);
  NT2_DISP(rref);
  it_t jb;
  
  nt2::tie(rref, jb) = nt2::rref(b);
  NT2_DISP(rref);
  NT2_DISP(jb);

}


