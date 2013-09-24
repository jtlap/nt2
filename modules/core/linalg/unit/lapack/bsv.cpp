//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/bsv.hpp>
#include <nt2/include/functions/gbcon.hpp>
#include <nt2/include/functions/langb.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(band, NT2_REAL_TYPES )
{
  using nt2::_;

  nt2::table<T, nt2::band_diagonal_<2,2> >  a = nt2::rand(7, 7, nt2::meta::as_<T>());
  nt2::table<T> b = nt2::rand(7, 1, nt2::meta::as_<T>());
  char norm = '1';
  nt2::table<nt2_la_int> piv;

  T anorm = nt2::langb(a,norm);
  nt2_la_int info = nt2::bsv(a,piv,b);

  T rnorm = nt2::gbcon(a,piv,anorm);

  NT2_TEST_EQUAL(info,T(0));
}
