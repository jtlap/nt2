//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::isempty function"

#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_isempty )
{
  NT2_TEST( !nt2::isempty('e') );
  NT2_TEST( !nt2::isempty(1)   );
  NT2_TEST( !nt2::isempty(1.)  );
  NT2_TEST( !nt2::isempty(1.f) );
}

NT2_TEST_CASE( container_isempty )
{
  NT2_TEST( nt2::isempty( nt2::ones(0))       );
  NT2_TEST( nt2::isempty( nt2::ones(0,1))     );
  NT2_TEST( nt2::isempty( nt2::ones(1,0))     );
  NT2_TEST( nt2::isempty( nt2::ones(0,1,1))   );
  NT2_TEST( nt2::isempty( nt2::ones(1,0,1))   );
  NT2_TEST( nt2::isempty( nt2::ones(1,1,0))   );
  NT2_TEST( nt2::isempty( nt2::ones(0,1,1,1)) );
  NT2_TEST( nt2::isempty( nt2::ones(1,0,1,1)) );
  NT2_TEST( nt2::isempty( nt2::ones(1,1,0,1)) );
  NT2_TEST( nt2::isempty( nt2::ones(1,1,1,0)) );

  NT2_TEST( !nt2::isempty( nt2::ones(4))        );
  NT2_TEST( !nt2::isempty( nt2::ones(2,3))      );
  NT2_TEST( !nt2::isempty( nt2::ones(3,1,2))    );
  NT2_TEST( !nt2::isempty( nt2::ones(3,3,1,9))  );
}
