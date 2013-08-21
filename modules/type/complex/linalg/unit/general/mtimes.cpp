//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::mtimes function"

#include <nt2/table.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/cons.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/include/constants/i.hpp>

NT2_TEST_CASE_TPL( mtimes, NT2_REAL_TYPES )
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  nt2::table<cT> y = nt2::cif(3, 4, nt2::meta::as_ < cT>())+nt2::I<cT>()*nt2::rif(3, 4, nt2::meta::as_ < cT>());
  nt2::table<cT> d = nt2::mtimes(y, trans(y));
  nt2::table<cT> c = nt2::trans(nt2::cons(nt2::of_size(3, 3),
                                          cT(26,20), cT(22,30), cT(18,40),
                                          cT(22,30), cT(14,40), cT(6,50),
                                          cT(18,40), cT(6,50), cT(-6,60)
                                         ));
  NT2_TEST_EQUAL(c, d);

 }
NT2_TEST_CASE_TPL( mtimes_1, NT2_REAL_TYPES )
{
  typedef typename nt2::meta::as_complex<T>::type  cT;
  nt2::table<T> y = nt2::cif(3, 4, nt2::meta::as_<T>());
  nt2::table<cT> yc = y;
  nt2::table<cT> z = nt2::ones(3, 3, nt2::meta::as_ < cT>());
  nt2::table<cT> d = nt2::mtimes(z, yc);
  nt2::table<cT> d1= nt2::mtimes(z, y);
  NT2_TEST_EQUAL(d, y*T(3));
  NT2_TEST_EQUAL(d1, d);

 }
