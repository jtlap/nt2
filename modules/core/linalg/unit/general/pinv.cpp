//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - pinv"

#include <nt2/table.hpp>
#include <nt2/include/functions/pinv.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/cond.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/log2.hpp>

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
    NT2_DISPLAY(n1);
    NT2_DISPLAY(pinvn1);
    p = mtimes(n1, pinvn1);
    NT2_DISPLAY(p);
    std::cout << nt2::log2(nt2::cond(n1)) << std::endl;
    std::cout << nt2::max(nt2::ulpdist(p, n)(nt2::_)) << std::endl;
    NT2_TEST(nt2::isulpequal(p, n, 2.5));
//     for(int i=1; i <= 3; i++)
//       {
//         NT2_TEST_ULP_EQUAL(p(i),n(i), 0.5);
//       }
  }
  {
    nt2::table<T> n = nt2::eye(3, 3, nt2::meta::as_<T>()), n1, p;
    n1 = n;
    n1(nt2::_, 1) = T(0.5);
    nt2::table<T> pinvn1 = nt2::pinv(n1);
    NT2_DISPLAY(n1);
    NT2_DISPLAY(pinvn1);
    p = mtimes(n1, pinvn1);
    NT2_DISPLAY(p);
    std::cout << nt2::log2(nt2::cond(n1)) << std::endl;
    std::cout << nt2::max(nt2::ulpdist(p, n)(nt2::_)) << std::endl;
    NT2_TEST(nt2::isulpequal(p, n, 2.5));
//     for(int i=1; i <= 3; i++)
//       {
//         NT2_TEST_ULP_EQUAL(p(i),n(i), 0.5);
//       }
  }
 }
