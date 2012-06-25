//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - rref factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/rref.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>

#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(rref, NT2_REAL_TYPES)
{
  typedef T r_t;
  typedef typename nt2::meta::as_integer<T, signed>::type  itype_t;
  typedef nt2::table<itype_t> it_t;
  using nt2::tag::factorization::rref_;
  T A[16] = {
   16,    2,    3,   13,
    5,   11,   10,    8,
    9,    7,    6,   12,
   4,   14,   15,    1};

  T R[16] = {
    1,    0,    0,    1,
    0,    1,    0,    3,
    0,    0,    1,   -3,
    0,    0,    0,    0};

  typedef nt2::table<T> t_t;
  typedef typename nt2::meta::call<rref_(t_t const&,T)>::type result_type;


  t_t a(nt2::of_size(4, 4));
  int k = 0;
  for(int i=1; i <= 4; ++i)
    {
      for(int j=1; j <= 4; ++j)
        {
          a(i, j) = A[k++];
        }
    }
  result_type f = nt2::factorization::rref(a, T(-1));

  NT2_DISPLAY(a);
  t_t r = f.rref();
  NT2_DISPLAY(r);
  k = 0;
  for(int i=1; i <= 4; ++i)
    {
      for(int j=1; j <= 4; ++j)
        {
          NT2_TEST_ULP_EQUAL(r(i, j),R[k], 1.0);
          ++k;
        }
    }
  it_t jb = f.jb();
  NT2_DISPLAY(jb);
}
