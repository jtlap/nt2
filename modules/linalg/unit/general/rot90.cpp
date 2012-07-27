//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - rot90 factorization"

#include <nt2/table.hpp>
#include <nt2/include/functions/rot90.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>

#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL(rot90, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::rot90;
  using nt2::tag::rot90_;

  nt2::table<T> n = nt2::cif(3, 3, nt2::meta::as_<T>())+T(10)*nt2::rif(3, 3, nt2::meta::as_<T>());
  NT2_DISPLAY(n);
  for(int i=1; i <= 4; ++i)
   {
     nt2::table<T> rot90n = nt2::rot90(n, i);
     std::cout << "i = " << i << std::endl;
     NT2_DISPLAY(rot90n);
   }
}

