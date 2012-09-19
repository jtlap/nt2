/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isulpequal function"

#include <nt2/table.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/nans.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE( fundamental_isulpequal )
{
  NT2_TEST( nt2::isulpequal('f', 'f') );
  NT2_TEST( nt2::isulpequal(1, 1)   );
  NT2_TEST( nt2::isulpequal(1., 1.)  );
  NT2_TEST( nt2::isulpequal(1.f, 1.f) );

  NT2_TEST( !nt2::isulpequal('r', 'e') );
  NT2_TEST( !nt2::isulpequal(int8_t('r'), int8_t('e'))); 
  NT2_TEST( !nt2::isulpequal(int('r'), int('e')));
  NT2_TEST( !nt2::isulpequal((short)(32750), (short)(32763))); 
  NT2_TEST( !nt2::isulpequal(1, 2)   );
  NT2_TEST( !nt2::isulpequal(1., 2.)  );
  NT2_TEST( !nt2::isulpequal(1.f, 2.0f) );
  NT2_TEST( nt2::isulpequal(nt2::Nan<float>(), nt2::Nan<float>()));
  std::cout << int(nt2::Valmax < char > ()) << std::endl;
  std::cout << int(nt2::Valmax < int8_t > ()) << std::endl;
  std::cout << int(nt2::Valmax < unsigned char > ()) << std::endl;
  std::cout << int(nt2::Valmax < uint8_t > ()) << std::endl;
  std::cout << nt2::Valmax < short > () << std::endl;
  std::cout << nt2::Valmax < int16_t > () << std::endl;
}

NT2_TEST_CASE( container_isulpequal )
{
  using nt2::_;
  nt2::table<float> a = nt2::ones(4, nt2::meta::as_<float>());
  nt2::table<float> b = nt2::ones(4, nt2::meta::as_<float>());

  NT2_TEST( nt2::isulpequal( a, b) );

  a(3, 3) = b(3, 3) = nt2::Nan<float>();
  NT2_TEST( nt2::isulpequal( a, b) );

  NT2_TEST( nt2::isulpequal( nt2::ones(4)      ,nt2::ones(4))       );
  NT2_TEST( nt2::isulpequal( nt2::ones(4,1)    ,nt2::ones(4,1))     );
  NT2_TEST( nt2::isulpequal( nt2::ones(4,1,1)  ,nt2::ones(4,1,1))   );
  NT2_TEST( nt2::isulpequal( nt2::ones(4,1,4,1),nt2::ones(4,1,4,1)) );

  NT2_TEST( !nt2::isulpequal( nt2::ones(2,3)    , nt2::ones(4))          );
  NT2_TEST( !nt2::isulpequal( nt2::ones(4,1)    , nt2::zeros(4,1))       );
  NT2_TEST( !nt2::isulpequal( nt2::ones(3,3,1,9), nt2::zeros(3,3,1,9)) );
  NT2_TEST(  nt2::isulpequal( nt2::ones(1, 1) , 1.0f));
  NT2_TEST( !nt2::isulpequal( nt2::ones(1, 2) , 1.0f));
  NT2_TEST(  nt2::isulpequal(1.0f ,  nt2::ones(1, 1)));
  NT2_TEST( !nt2::isulpequal(1.0f ,  nt2::ones(1, 2)));
  NT2_TEST(  nt2::isulpequal( nt2::ones(1, 1) , 1.0f));
  NT2_TEST( !nt2::isulpequal( nt2::ones(1, 2) , 1.0f));
  NT2_TEST(  nt2::isulpequal( nt2::Nan<float>(),  nt2::nans(1, 1)));
  NT2_TEST( !nt2::isulpequal( nt2::Nan<float>(),  nt2::nans(1, 2)));
}
