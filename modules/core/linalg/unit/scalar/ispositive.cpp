//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ispositive.hpp>
#include <nt2/include/functions/cov.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>


NT2_TEST_CASE_TPL( table_ispositive, NT2_REAL_TYPES )
{
  typedef T type;
  nt2::table<type> a(nt2::of_size(3, 3)), b(nt2::of_size(3, 3)), c(nt2::of_size(3, 3));
  for(std::ptrdiff_t i=1; i <= 3; i++)
   {
     for(std::ptrdiff_t j=1; j <= 3; j++)
       {
         a(i, j) = (i == j) ? T(10) :float(i+j);
         b(i, j) = (i == j) ? T(-10) :float(i+j);
       }
   }
  NT2_TEST( nt2::ispositive(a));
  NT2_TEST( !nt2::ispositive(b));

}
NT2_TEST_CASE_TPL( table_ispositive2, NT2_REAL_TYPES )
{
  typedef T type;
  nt2::table<type> a = nt2::cons<T>(nt2::of_size(30, 4),
                                    3, 54, 55, 32, 50, 26, 70, 7, 45, 1, 108, 40, 116, 28, 46, 16, 20, 15, 56, 98, 13, 66, 29, 104, 64, 96, 91, 115, 97, 99,
                                    94, 51, 27, 30, 43, 109,  9, 112, 14, 62, 117, 92, 76, 101, 118, 37, 85, 23, 52, 67, 39, 82, 42, 8, 25, 44, 110, 31, 119, 103,
                                    11, 100, 74, 107, 75, 60, 93, 73, 36, 35, 120, 77, 78, 24, 84, 61, 19, 88, 49, 18, 90, 111, 113, 22, 89, 68, 81, 59, 57, 65,
                                    114, 58, 63, 4, 72, 69, 41, 80, 10, 83, 5, 79, 53, 95, 21, 6, 17, 87, 38, 33, 105, 12, 102, 71, 86, 47, 34, 48, 2, 106
                                   );
  nt2::table<type> c =  nt2::cov(a);
  NT2_TEST( nt2::ispositive(c));
}
