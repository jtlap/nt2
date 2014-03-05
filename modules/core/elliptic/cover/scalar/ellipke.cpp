//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
// cover for functor ellik in scalar mode
#include <nt2/elliptic/include/functions/ellipke.hpp>

#include <boost/simd/sdk/simd/io.hpp>
#include <cmath>
#include <iostream>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/ellpk.hpp>
#include <nt2/include/functions/ellpe.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/unit/args.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/cover.hpp>
#include <vector>

template < class T > struct ellipk1
{
  T operator()(const T & x)
  {
    T a1 = nt2::Zero<T>();
    T a0 = nt2::ellipke(x, nt2::Eps<T>(),a1);
    return a0;
  }
};

 template < class T > struct ellipk2
{
  T operator()(const T & x)
  {
    T a1 = nt2::Zero<T>();
    T a0 = nt2::ellipke(x, nt2::Eps<T>(), a1);
    return a1;
  }
};


NT2_TEST_CASE_TPL(ellpk_0,  NT2_SIMD_REAL_TYPES)
{
  using nt2::unit::args;
  const std::size_t NR = args("samples", NT2_NB_RANDOM_TEST);
  const double ulpd = args("ulpd", 2);

  typedef typename nt2::meta::as_integer<T>::type iT;
  const T min0 = args("min0", T(0));
  const T max0 = args("max0", T(1));
  std::cout << "Argument samples #0 chosen in range: [" << min0 << ",  " << max0 << "]" << std::endl;
  NT2_CREATE_BUF(a0,T, NR, min0, max0);

  std::vector<T> ref1(NR), ref2(NR);
  for(std::size_t i=0; i!=NR; ++i)
  {
    ref1[i] = nt2::ellpk(nt2::oneminus(a0[i]));
    ref2[i] = nt2::ellpe(nt2::oneminus(a0[i]));
  }

  NT2_COVER_FN_ULP_EQUAL(ellipk1<T>() , ((T, a0)), ref1, ulpd);
  NT2_COVER_FN_ULP_EQUAL(ellipk2<T>() , ((T, a0)), ref2, ulpd);

}

