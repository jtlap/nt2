//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/histc.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/table.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/table.hpp>
#include <boost/simd/sdk/simd/io.hpp>

// NT2_TEST_CASE_TPL( histc, NT2_REAL_TYPES )
// {
//   using nt2::table;
//   using nt2::histc;

//   table<T> x = nt2::linspace(T(-10), T(10), 10000);
//   table<std::size_t> h =  histc(x, 20);
// //  NT2_DISPLAY(h);
// //  NT2_TEST_EQUAL(h, nt2::repnum(std::size_t(500), 20, 1));
// }

NT2_TEST_CASE_TPL( histc2, NT2_REAL_TYPES )
{
  using nt2::table;
  using nt2::histc;

  table<T> x = nt2::linspace(T(-10), T(10), 10000);
  table<T> bins =  nt2::linspace(T(-11), T(11), 10);
  table<std::size_t> h =  histc(x, bins, 2);
  NT2_DISPLAY(h);
  NT2_TEST_EQUAL(h, nt2::repnum(std::size_t(500), 1, 10));
}


// NT2_TEST_CASE_TPL( pipo1, (float) )
// {
//   using nt2::table;
//   using nt2::histc;

//   table<T> x = nt2::linspace(T(-10), T(10), 10000);
//   table<T> bins =  nt2::linspace(T(-11), T(11), 10);
//   int dim = 2;
//   int i = 1;
//   auto z =  nt2::inbtrue(nt2::logical_and(ge(x, bins(i)), lt(x,  bins(i+1))), dim);
//   std::cout << "z" << z << std::endl;
//   table<unsigned int > zz =  nt2::inbtrue(nt2::logical_and(nt2::ge(x, bins(i)), nt2::lt(x,  bins(i+1))), dim);
//   std::cout << "zz" << zz << std::endl;
// }


// NT2_TEST_CASE_TPL( pipo2, (float) )
// {
//   using nt2::table;
//   using nt2::histc;
//   using nt2::size;

//   table<T> x = nt2::linspace(T(-10), T(10), 10000);
//   table<T> bins =  nt2::linspace(T(-11), T(11), 10);
//   int dim = 2;
//   auto sizee = x.extent();
//   std::size_t n = numel(bins);
//   sizee[dim-1] = n-1;
//   table<unsigned int > h(sizee);
//   table<unsigned int > r =  cons<std::size_t>( 723, 1222, 1222, 1222, 1222, 1222, 1222, 1222, 723 );
//   for(std::size_t i=1; i < n ; ++i)
//   {
//     along(h, i, dim) = inbtrue(logical_and(ge(x, bins(i)), lt(x,  bins(i+1))), dim);
//   }
//    std::cout << "h     " << h << std::endl;
//    NT2_TEST_EQUAL(h, r);
// }
