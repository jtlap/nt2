/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isexpandable_to function"

#include <nt2/include/functions/isexpandable_to.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_isexpandable_to )
{
  NT2_TEST( nt2::isexpandable_to(1.f, nt2::of_size(3, 4)));
}

NT2_TEST_CASE( container_isexpandable_to )
{
  for(int i=1; i <= 4; ++i)
  {
    NT2_TEST( nt2::isexpandable_to( nt2::ones(0),      nt2::of_size(0)       ));
    NT2_TEST( nt2::isexpandable_to( nt2::ones(1,0),    nt2::of_size(1,0)  ));

    NT2_TEST( nt2::isexpandable_to( nt2::ones(1),      nt2::of_size(1,4)  ));
    NT2_TEST( nt2::isexpandable_to( nt2::ones(1,3),    nt2::of_size(3,3)  ));
    NT2_TEST( nt2::isexpandable_to( nt2::ones(1,3,1),  nt2::of_size(1,3,3)   ));
    NT2_TEST( !nt2::isexpandable_to( nt2::ones(2,3),nt2::of_size(3,3) ));

    NT2_TEST( nt2::isexpandable_to( nt2::ones(3, 1),     nt2::of_size(3)        ));
    NT2_TEST( nt2::isexpandable_to( nt2::ones(2,3),   nt2::of_size(2,3)      ));
    NT2_TEST( nt2::isexpandable_to( nt2::ones(1,3,2), nt2::of_size(1,3,2)    ));
    NT2_TEST( nt2::isexpandable_to( nt2::ones(1,3,1,9), nt2::of_size(1,3,1,9)));
  }
}
