//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/linalg/details/utility/llspgen.hpp>
#include <nt2/include/functions/sne.hpp>
#include <nt2/include/functions/csne.hpp>
#include <nt2/include/functions/mcsne.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <sys/time.h>

NT2_TEST_CASE_TPL(sne, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a,x,r,b;

  size_t m=20,n=10,q=1,nr=1;

  nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr,nt2::meta::as_<T>());

  t_t s1 = nt2::sne(a,b);
  t_t s2 = nt2::linsolve(a,b);

  NT2_TEST_ULP_EQUAL(s1(_(1,n)), s2(_(1,n)), T(100));
}


NT2_TEST_CASE_TPL(csne, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a,x,r,b;

  size_t m=20,n=10,q=1,nr=1;

  nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr,nt2::meta::as_<T>());

  t_t s1 = nt2::csne(a,b);

  t_t s2 = nt2::linsolve(a,b);

  NT2_TEST_ULP_EQUAL(s1, s2(_(1,n)), T(100));
}

NT2_TEST_CASE_TPL(msne, (double) )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a,x,r,b;
  size_t m=2000,n=1000,q=1,nr=1;

  nt2::tie(a,x,r,b)= nt2::llspgen(m,n,q,nr, nt2::meta::as_<T>());

  t_t s1 = nt2::mcsne(a,b);
  t_t s2 = nt2::linsolve(a,b);

  NT2_TEST_ULP_EQUAL(s1(_(1,n)), s2(_(1,n)), T(10000000));
}

