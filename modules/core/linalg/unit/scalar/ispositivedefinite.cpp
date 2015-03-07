//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ispositivedefinite.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

// NT2_TEST_CASE( fundamental_ispositivedefinite )
// {
//   NT2_TEST( nt2::ispositivedefinite(1.)  );
//   NT2_TEST( nt2::ispositivedefinite(1.f) );
// }

NT2_TEST_CASE_TPL( table_ispositivedefinite, NT2_REAL_TYPES )
{
  typedef float type;
  nt2::table<type> a(nt2::of_size(3, 3)), b(nt2::of_size(3, 3));
  for(std::ptrdiff_t i=1; i <= 3; i++)
   {
     for(std::ptrdiff_t j=1; j <= 3; j++)
       {
         a(i, j) = (i == j) ? T(10) :float(i+j);
         b(i, j) = (i == j) ? T(-10) :float(i+j);
       }
   }
  NT2_TEST( nt2::ispositivedefinite(a));
  NT2_TEST( !nt2::ispositivedefinite(b));

}
