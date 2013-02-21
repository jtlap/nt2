//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/rem_pio2.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/cos.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/constants/pi.hpp>


#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(rem_pio2_table, NT2_REAL_TYPES)
{
  using nt2::rem_pio2;
  using nt2::table;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef table<iT> tabi_t;
  typedef table<T> tab_t;
  static const size_t nb = 60;
  tab_t a = nt2::linspace(T(0), T(10)*nt2::Pi<T>(), nb);
  tab_t  r(nt2::of_size(1, nb));
  tabi_t  n(nt2::of_size(1, nb));
  {
    tie(n, r) = rem_pio2(a);
    for(size_t i = 1; i <= nb; ++i)
    {
      iT n1;
      T r1;
      n1 = rem_pio2(a(i), r1);
//       std::cout<< " ai  "  << a(i)                  << std::endl;
//       std::cout<< " n1  "  << n1   << " r1  " << r1 << std::endl;
//       std::cout<< " ni  "  << n(i) << " ri  " << r(i) << std::endl;
      NT2_TEST_EQUAL(n(i), n1);
      NT2_TEST_EQUAL(r(i), r1);
    }

  }

  {
    n = rem_pio2(a, r);
    for(size_t i = 1; i <= nb; ++i)
    {
      iT n1;
      T r1;
      n1 = rem_pio2(a(i), r1);
      NT2_TEST_EQUAL(n(i), n1);
      NT2_TEST_EQUAL(r(i), r1);
    }
  }

  {
    nt2::tie(n, r) = rem_pio2(a);
    for(size_t i = 1; i <= nb; ++i)
    {
      iT n1;
      T r1;
      n1 = rem_pio2(a(i), r1);
      NT2_TEST_EQUAL(n(i), n1);
      NT2_TEST_EQUAL(r(i), r1);
    }
  }
}
