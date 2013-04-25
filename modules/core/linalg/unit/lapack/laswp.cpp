//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/laswp.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(laswp, NT2_REAL_TYPES )
{
  using nt2::_;

  typedef nt2::table<T>           t_t;
  typedef nt2::table<nt2_la_int>  t_i;

  t_t a = nt2::zeros(7, 7, nt2::meta::as_<T>());
  t_i ipiv( nt2::of_size(7));

  for(std::size_t i=1;i<=7;++i)
  {
    a(i,7-i+1) = 1;

  }

  ipiv(1) = 7;
  ipiv(2) = 6;
  ipiv(3) = 5;
  ipiv(4) = 4;
  ipiv(5) = 5;
  ipiv(6) = 6;
  ipiv(7) = 7;

  nt2::laswp(a,ipiv);

  NT2_TEST_EQUAL(a, nt2::eye(7, 7, nt2::meta::as_<T>()) );
}
