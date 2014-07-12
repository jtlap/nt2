//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/arecatcompatible.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( container )
{
  for(int i=1; i <= 4; ++i)
  {
    nt2::table<int> empty_table;
    NT2_TEST( nt2::arecatcompatible( empty_table, empty_table, i ));

    NT2_TEST( nt2::arecatcompatible( nt2::ones(0),      nt2::ones(0)       , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(1,0),    nt2::ones(1,0)     , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(2,0,2),  nt2::ones(2,0,2)   , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(3,3,0,1),nt2::ones(3,3,0,1) , i ));

    NT2_TEST( nt2::arecatcompatible( nt2::ones(1),      nt2::ones(1)       , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(1,3),    nt2::ones(1,3)     , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(1,3,1),  nt2::ones(1,3,1)   , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(1,3,1,1),nt2::ones(1,3,1,1) , i ));

    NT2_TEST( nt2::arecatcompatible( nt2::ones(3),     nt2::ones(3)       , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(2,3),   nt2::ones(2,3)     , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(1,3,2), nt2::ones(1,3,2)   , i ));
    NT2_TEST( nt2::arecatcompatible( nt2::ones(1,3,1,9), nt2::ones(1,3,1,9), i ));
  }
}
