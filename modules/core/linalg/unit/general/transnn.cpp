//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/transnn.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/reshape.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>



NT2_TEST_CASE_TPL( transnn, NT2_REAL_TYPES )
{
  {
//    nt2::table<T, nt2::of_size_<1, 1 > > y;
//     y(1) = T(3);
//     nt2::table<T, nt2::of_size_<1, 1 > > ty;
//     ty =  nt2::transnn<1,1>(y);
//     NT2_TEST_EQUAL(ty, y);
  }

  {
    nt2::table<T, nt2::of_size_<2, 1 >> y = nt2::ones(2, 1, nt2::meta::as_<T>()); ;
    nt2::table<T, nt2::of_size_<1, 2 >> ty;
    ty =  nt2::transnn<2,1>(y);
    NT2_TEST_EQUAL(ty, nt2::trans(y));
  }

  {
    nt2::table<T, nt2::of_size_<1, 2>> y = nt2::ones(1, 2, nt2::meta::as_<T>()); ;
    nt2::table<T, nt2::of_size_<2, 1>> ty;
    ty =  nt2::transnn<1, 2>(y);
    NT2_TEST_EQUAL(ty, nt2::trans(y));
  }

  {
    nt2::table<T, nt2::of_size_<2, 2>> y = nt2::reshape(nt2::_(T(1), T(4)), 2, 2);
    nt2::table<T, nt2::of_size_<2, 2>> ty;
    ty =  nt2::transnn<2, 2>(y);
    NT2_TEST_EQUAL(ty, nt2::trans(y));
  }

  {
    nt2::table<T, nt2::of_size_<3, 3>> y = nt2::reshape(nt2::_(T(1), T(9)), 3, 3);
    nt2::table<T, nt2::of_size_<3, 3>> ty;
    ty =  nt2::transnn<3, 3>(y);
    NT2_TEST_EQUAL(ty, nt2::trans(y));
  }
  {
    nt2::table<T, nt2::of_size_<3, 2>> y = nt2::reshape(nt2::_(T(1), T(6)), 3, 2);
    nt2::table<T, nt2::of_size_<2, 3>> ty;
    ty =  nt2::transnn<3, 2>(y);
    NT2_TEST_EQUAL(ty, nt2::trans(y));
  }
  {
    nt2::table<T, nt2::of_size_<2, 3>> y = nt2::reshape(nt2::_(T(1), T(6)), 2, 3);
    nt2::table<T, nt2::of_size_<3, 2>> ty;
    ty =  nt2::transnn<2, 3>(y);
    NT2_TEST_EQUAL(ty, nt2::trans(y));
  }
  {
    nt2::table<T, nt2::of_size_<4, 4>> y = nt2::reshape(nt2::_(T(1), T(16)), 4, 4);
    nt2::table<T, nt2::of_size_<4, 4>> ty;
    ty =  nt2::transnn<4, 4>(y);
    NT2_TEST_EQUAL(ty, nt2::trans(y));
  }
}



