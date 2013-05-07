//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::diag_of function"

#include <nt2/table.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/isempty.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>


NT2_TEST_CASE_TPL( diag_of_exprc, NT2_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> x,y( nt2::of_size(7,7) );

  for(int j=1;j<=7;j++)
    for(int i=1;i<=7;i++)
      y(i,j) = cT(i + 10*j, j);

  x = nt2::diag_of(y, 1);

  for(size_t i=1;i<=nt2::length(x);i++)
    NT2_TEST_EQUAL( x(i), y(i,i+1) );
}
