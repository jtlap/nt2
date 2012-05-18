/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isvectoralong function"

#include <nt2/include/functions/isvectoralong.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_isvectoralong )
{
  NT2_TEST( nt2::isvectoralong('e', 1) );
  NT2_TEST( nt2::isvectoralong(1, 2)   );
  NT2_TEST( nt2::isvectoralong(1., 3)  );
  NT2_TEST( nt2::isvectoralong(1.f, 4) );
}

NT2_TEST_CASE( container_isvectoralong )
{
  NT2_TEST(!nt2::isvectoralong( nt2::ones(4)     , 1  ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(4,1)     , 1 ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(4,1,1)   , 1 ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(4,1,1,1) , 1 ));

  NT2_TEST( nt2::isvectoralong( nt2::ones(1)      , 2 ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(1,4)    , 2 ));
  NT2_TEST( !nt2::isvectoralong( nt2::ones(1,4)    , 1 ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(1,4,1)  , 2 ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(1,4,1,1), 2 ));

  NT2_TEST( nt2::isvectoralong( nt2::ones(1,1,3) , 3 ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(1,1,2) , 3 ));
  NT2_TEST( nt2::isvectoralong( nt2::ones(1,1,3,1), 3 ));

}
