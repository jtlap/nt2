//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - orth"

#include <nt2/table.hpp>
#include <nt2/include/functions/orth.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/norm.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL(orth, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef T r_t;
  using nt2::orth;
  using nt2::tag::orth_;
  std::cout << std::setprecision(20);
  nt2::table<cT> n = nt2::eye(10, 10, nt2::meta::as_<cT>());
  n(3, 5) = cT(2);
  n(4, 4) = cT(0);
  n(1, 1) = cT(5)*nt2::Eps<T>();
  nt2::table<cT> orthn = nt2::orth(n);
  nt2::table<cT> orthn1 = nt2::orth(n,  100*nt2::Eps<T>());
  T rn[100] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0.92387953251128673848, 0, -0, 0, 0, 0, 0, -0.38268343236508972627,
    0, 0, -0, 0, 0, 0, 0, 0,
    0.38268343236508972627, 0, -0, 0, 0, 0, 0, 0.92387953251128673848,
    -0, 0, -0, 0, 0, 1, 0, 0,
    -0, 0, -0, 0, 0, -0, 1, 0,
    -0, 0, -0, 1, 0, -0, -0, 0,
    -0, 1, -0, -0, 0, -0, -0, 0,
    -0, -0, -0, -0, 1, -0, -0, 0
  };
  int k = 0;
  nt2::table<cT> a(nt2::of_size(10, 8));
  for(int i=1; i <= 10; i++)
    {
      for(int j=1; j <= 8; j++)
        {
          a(i, j) = rn[k++];
        }
    }
  NT2_TEST_ULP_EQUAL(a, orthn1, 1.0);
}

NT2_TEST_CASE_TPL(orth2, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  typedef T r_t;
  using nt2::orth;
  using nt2::tag::orth_;
  std::cout << std::setprecision(20);
  nt2::table<cT> n = nt2::sqr(nt2::reshape(nt2::_(T(1), T(16)), 4, 4))+
    nt2::I<cT>()*nt2::sqrt(nt2::reshape(nt2::_(T(16), T(-1), T(1)), 4, 4)*T(5));
  nt2::table<cT> orthn = nt2::orth(n);
  NT2_TEST_LESSER_EQUAL(nt2::norm(nt2::mtimes(orthn, nt2::trans(nt2::conj(orthn)))-nt2::eye(4, nt2::meta::as_<cT>())), T(5)*nt2::Eps<T>());
}
