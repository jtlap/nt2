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
#include <nt2/include/functions/cond.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/log2.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL(pinv, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  using nt2::pinv;
  using nt2::tag::pinv_;
  using nt2::mtimes;
  {
    nt2::table<cT> n = nt2::eye(3, 3, nt2::meta::as_<cT>()), n1, p;
    n1 = n;
    n1(nt2::_, 1) = cT(0.5);
    nt2::table<cT> pinvn1 = nt2::pinv(n1, nt2::Eps<T>());
    p = mtimes(n1, pinvn1);
    NT2_TEST_ULP_EQUAL(p, n, 2.5);
  }
  {
    nt2::table<cT> n = nt2::eye(3, 3, nt2::meta::as_<cT>()), n1, p;
    n1 = n;
    n1 += nt2::I<cT>()*n1;
    n1(nt2::_, 1) = cT(0.5);
    nt2::table<cT> pinvn1 = nt2::pinv(n1);
    p =  mtimes(mtimes(n1, pinvn1), n1);
    NT2_TEST_LESSER_EQUAL(norm(p-n1, 2), T(10)*nt2::Eps<T>());
    p =  mtimes(mtimes(pinvn1, n1), pinvn1);
    NT2_TEST_LESSER_EQUAL(norm(p-pinvn1, 2), T(10)*nt2::Eps<T>());
  }
}
