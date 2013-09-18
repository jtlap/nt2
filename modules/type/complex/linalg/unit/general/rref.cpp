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

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>


template <class T, class S> nt2::table<T> make_matrix( const S * ptr, int nl, int nc)
{
  nt2::table<T> a(nt2::of_size(nl, nc));
  const S* p = ptr; ;
  for(int i = 1; i <= nl; ++i)
    for(int j = 1; j <= nc; ++j)
      a(i, j) = *p++;
  return a;
}

NT2_TEST_CASE_TPL(rref, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
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

  typedef nt2::table<cT> t_t;
  typedef typename nt2::meta::call<rref_(t_t const&,T)>::type result_type;

  t_t a =  make_matrix<T>(&A[0], 4, 4)*cT(1, 1);
  t_t res =  make_matrix<T>(&R[0], 4, 4);
  result_type f = nt2::factorization::rref(a, T(-1));
  t_t r = f.rref();
  NT2_TEST_ULP_EQUAL(r, res, 10.0);
  it_t jb = f.jb();
  NT2_TEST_EQUAL(jb, nt2::_(itype_t(1), itype_t(3)));
}
