/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isvector function"

#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_isvector )
{
  NT2_TEST( nt2::isvector('e') );
  NT2_TEST( nt2::isvector(1)   );
  NT2_TEST( nt2::isvector(1.)  );
  NT2_TEST( nt2::isvector(1.f) );
}

NT2_TEST_CASE( container_isvector )
{
  NT2_TEST( !nt2::isvector( nt2::ones(4))       );
  NT2_TEST( nt2::isvector( nt2::ones(4,1))     );
  NT2_TEST( nt2::isvector( nt2::ones(4,1,1))   );
  NT2_TEST( nt2::isvector( nt2::ones(4,1,1,1)) );

  NT2_TEST( nt2::isvector( nt2::ones(1))       );
  NT2_TEST( nt2::isvector( nt2::ones(1,4))     );
  NT2_TEST( nt2::isvector( nt2::ones(1,4,1))   );
  NT2_TEST( nt2::isvector( nt2::ones(1,4,1,1)) );

  NT2_TEST( !nt2::isvector( nt2::ones(2,3))     );
  NT2_TEST( !nt2::isvector( nt2::ones(3,1,2))   );
  NT2_TEST( !nt2::isvector( nt2::ones(3,3,1,9)) );

  NT2_TEST( !nt2::isvector( nt2::ones(2,3))     );
  NT2_TEST( !nt2::isvector( nt2::ones(3,1,2))   );
  NT2_TEST( !nt2::isvector( nt2::ones(1,3,1,9)) );
}
