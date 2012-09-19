/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::arecatcompatible function"

#include <nt2/include/functions/arecatcompatible.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_arecatcompatible )
{
  NT2_TEST( nt2::arecatcompatible('e', 'e', 1));
  NT2_TEST( nt2::arecatcompatible(1,   1  , 1));
  NT2_TEST( nt2::arecatcompatible(1.,  1. , 1));
  NT2_TEST( nt2::arecatcompatible(1.f, 1.f, 1));
}

NT2_TEST_CASE( container_arecatcompatible )
{
  
  for(int i=1; i <= 4; ++i)
    {
      std::cout << "i " << i << std::endl; 
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
