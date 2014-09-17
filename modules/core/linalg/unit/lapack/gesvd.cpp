//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/gesvd.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(gesvd, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;

  t_t a0 = nt2::rand(10,10,nt2::meta::as_<T>());
  t_t a(a0);
  t_t s(nt2::of_size(10,1));
  t_t u(nt2::of_size(10,10));
  t_t vt(nt2::of_size(10,10));
  char jobu ='A';
  char jobvt ='A';

  nt2_la_int info = nt2::gesvd(boost::proto::value(a0),boost::proto::value(s)
                              ,boost::proto::value(u), boost::proto::value(vt)
                              ,jobu,jobvt);

  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,nt2::from_diag(s)),vt), a,T(450));

  NT2_TEST_EQUAL(info, 0);

}



NT2_TEST_CASE_TPL(gesvdc, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef std::complex<T>         cT;
  typedef nt2::table<cT>          t_t;

  t_t a0 = nt2::ones(10, 10, nt2::meta::as_<cT>())
          +nt2::eye(10, 10, nt2::meta::as_<cT>());
  t_t a(a0);
  nt2::table<T> s(nt2::of_size(10,1));
  t_t u(nt2::of_size(10,10));
  t_t vt(nt2::of_size(10,10));
  char jobu ='A';
  char jobvt ='A';

  nt2_la_int info = nt2::gesvd(boost::proto::value(a0),boost::proto::value(s)
                              ,boost::proto::value(u), boost::proto::value(vt)
                              ,jobu,jobvt);

  NT2_TEST_ULP_EQUAL(nt2::mtimes(nt2::mtimes(u,nt2::from_diag(nt2::complexify(s))),vt), a,T(200));

  NT2_TEST_EQUAL(info, 0);
}

