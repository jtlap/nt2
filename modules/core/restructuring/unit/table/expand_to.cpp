//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::expand_to function"

#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( of_size, NT2_TYPES)
{
  nt2::table<T> in, ref, out;

  in  = nt2::rif(nt2::of_size(1), nt2::meta::as_<T>());
  ref = nt2::ones(nt2::of_size(3), nt2::meta::as_<T>());
  out = expand_to(in, nt2::of_size(3));
  NT2_TEST_EQUAL(out,ref);

  in  = nt2::rif(nt2::of_size(3,1), nt2::meta::as_<T>());
  ref = nt2::rif(nt2::of_size(3, 4), nt2::meta::as_<T>());
  out = expand_to(in, nt2::of_size(3, 4));
  NT2_TEST_EQUAL(out,ref);

  in  = nt2::cif(nt2::of_size(1,4), nt2::meta::as_<T>());
  ref = nt2::cif(nt2::of_size(3, 4), nt2::meta::as_<T>());
  out = expand_to(in, nt2::of_size(3, 4));
  NT2_TEST_EQUAL(out,ref);

  in  = nt2::cif(nt2::of_size(1,2,1), nt2::meta::as_<T>());
  ref = nt2::cif(nt2::of_size(3,2,3), nt2::meta::as_<T>());
  out = expand_to(in, nt2::of_size(3, 2,3));
  NT2_TEST_EQUAL(out,ref);
}
