//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gallery toolbox - randjorth function"

#include <nt2/table.hpp>
#include <nt2/include/functions/randjorth.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/blkdiag.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/cond.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>


NT2_TEST_CASE_TPL ( randjorth, NT2_REAL_TYPES)
{
  nt2::table<T> rc, p;
  nt2::table<T> j = nt2::blkdiag(nt2::eye(2, nt2::meta::as_<T>()),
                                 -nt2::eye(2, nt2::meta::as_<T>()));
  rc = nt2::randjorth(2, 2, nt2::rec(nt2::Sqrteps<T>()), 1);
  p  = nt2::mtimes( nt2::mtimes(nt2::transpose(rc), j), rc);
  NT2_TEST_LESSER(nt2::abs(nt2::cond(rc)-nt2::rec(nt2::Sqrteps<T>())), T(1));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(j-p)), nt2::Two<T>()*nt2::Sqrteps<T>());

  rc = nt2::randjorth(2, 2, nt2::rec(nt2::Sqrteps<T>()), 0);
  p  = nt2::mtimes( nt2::mtimes(nt2::transpose(rc), j), rc);
  NT2_TEST_LESSER(nt2::abs(nt2::cond(rc)-nt2::rec(nt2::Sqrteps<T>())), T(1));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(j-p)),  nt2::Two<T>()*nt2::Sqrteps<T>());

  rc = nt2::randjorth(3, 4, T(2));
  j = nt2::blkdiag(nt2::eye(3, nt2::meta::as_<T>()),
                   -nt2::eye(4, nt2::meta::as_<T>()));
  p  = nt2::mtimes( nt2::mtimes(nt2::transpose(rc), j), rc);
  NT2_TEST_LESSER(nt2::abs(nt2::cond(rc)-T(2)), T(1.0e-3));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(j-p)),  nt2::Two<T>()*nt2::Sqrteps<T>());

  rc = nt2::randjorth(4, 3, T(2));
  j = nt2::blkdiag(nt2::eye(4, nt2::meta::as_<T>()),
                   -nt2::eye(3, nt2::meta::as_<T>()));
  p  = nt2::mtimes( nt2::mtimes(nt2::transpose(rc), j), rc);
  NT2_TEST_LESSER(nt2::abs(nt2::cond(rc)-T(2)), T(1.0e-3));
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(j-p)),  nt2::Two<T>()*nt2::Sqrteps<T>());

}






