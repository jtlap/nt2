//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/homot.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( homot, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> ref = nt2::zeros( nt2::of_size(3,3), nt2::meta::as_<cT>());
  for(std::size_t i=1;i<= length(ref);++i) ref(i, i) = cT(42, 2);

  nt2::table<cT> x0 = nt2::homot(cT(42, 2),3);
  NT2_TEST_EQUAL( x0,ref );
  ref = nt2::zeros( nt2::of_size(8,8), nt2::meta::as_<T>() );
  for(std::size_t i=1;i<= length(ref);++i) ref(i, i) = cT(42, 2);

  nt2::table<cT> x1 = nt2::homot(cT(42, 2),nt2::of_size(8, 8));
  NT2_TEST_EQUAL(x1,ref);

  nt2::table<cT> x2 = nt2::homot(cT(42, 2), 8, 8 );
  NT2_TEST_EQUAL(x2,ref);
}

