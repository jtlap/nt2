//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/lyapunov.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/core/container/colon/colon.hpp>

NT2_TEST_CASE_TPL(lyapunov0, NT2_REAL_TYPES)
{
  NT2_TEST_EQUAL(nt2::lyapunov(T(2), T(4)), T(1));
 }

NT2_TEST_CASE_TPL(lyapunov1, NT2_REAL_TYPES)
{
  using nt2::lyapunov;
  using nt2::tag::lyapunov_;
  nt2::table<T> a =  nt2::triu(nt2::reshape(nt2::_(T(1), T(9)), 3, 3));
  nt2::table<T> x =  nt2::tril(nt2::reshape(nt2::_(T(1), T(9)), 3, 3));
  nt2::table<T> c =  nt2::mtimes(ctrans(a), x)+nt2::mtimes(x, a);
  nt2::table<T> r =  lyapunov(a, c);
  std::cout << nt2::globalmax(nt2::abs(r-x)) << std::endl;
  NT2_TEST_LESSER(nt2::globalmax(nt2::abs(r-x)), nt2::Eps<T>()*numel(x));

 }

