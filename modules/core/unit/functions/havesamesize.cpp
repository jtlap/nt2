/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::havesamesize function"

#include <nt2/include/functions/havesamesize.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_havesamesize )
{
  NT2_TEST( nt2::havesamesize('e', 'r') );
  NT2_TEST( nt2::havesamesize(1, 2)   );
  NT2_TEST( nt2::havesamesize(1., 2)  );
  NT2_TEST( nt2::havesamesize(1.f, 2.0) );
}

NT2_TEST_CASE( container_havesamesize )
{
  NT2_TEST( nt2::havesamesize( nt2::ones(4)      ,nt2::ones(4)      ));
  NT2_TEST( nt2::havesamesize( nt2::ones(4,1)    ,nt2::ones(4,1)    ));
  NT2_TEST( nt2::havesamesize( nt2::ones(4,1,1)  ,nt2::ones(4,1,1)  ));
  NT2_TEST( nt2::havesamesize( nt2::ones(4,1,4,1),nt2::ones(4,1,4,1)));
                                                                     
  NT2_TEST( !nt2::havesamesize( nt2::ones(2,3)    , nt2::ones(4)    ));
  NT2_TEST( !nt2::havesamesize( nt2::ones(3,1,2)  , nt2::ones(4,1)  ));
  NT2_TEST( !nt2::havesamesize( nt2::ones(3,3,1,9), nt2::ones(4,1,1)));

}
