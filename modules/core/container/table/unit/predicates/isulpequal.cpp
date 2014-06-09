//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/nan.hpp>

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
}

NT2_TEST_CASE_TPL( container_isulpequal, NT2_REAL_TYPES )
{
  using nt2::_;

  nt2::meta::as_<T> tgt;

  nt2::table<T> a = nt2::ones(4, tgt);
  nt2::table<T> b = nt2::ones(4, tgt);

  NT2_TEST( nt2::isulpequal( a, b) );

  a(3, 3) = b(3, 3) = nt2::Nan<T>();
  NT2_TEST( nt2::isulpequal( a, b) );

  NT2_TEST( nt2::isulpequal( nt2::ones(4, tgt)      ,nt2::ones(4, tgt))       );
  NT2_TEST( nt2::isulpequal( nt2::ones(4,1, tgt)    ,nt2::ones(4,1, tgt))     );
  NT2_TEST( nt2::isulpequal( nt2::ones(4,1,1, tgt)  ,nt2::ones(4,1,1, tgt))   );
  NT2_TEST( nt2::isulpequal( nt2::ones(4,1,4,1, tgt),nt2::ones(4,1,4,1, tgt)) );

  NT2_TEST( !nt2::isulpequal( nt2::ones(2,3, tgt)    , nt2::ones(4, tgt))        );
  NT2_TEST( !nt2::isulpequal( nt2::ones(4,1, tgt)    , nt2::zeros(4,1, tgt))     );
  NT2_TEST( !nt2::isulpequal( nt2::ones(3,3,1,9, tgt), nt2::zeros(3,3,1,9, tgt)) );
  NT2_TEST(  nt2::isulpequal( nt2::ones(1, 1, tgt) , T(1)) );
  NT2_TEST( !nt2::isulpequal( nt2::ones(1, 2, tgt) , T(1)) );
  NT2_TEST(  nt2::isulpequal( T(1),  nt2::ones(1, 1, tgt)) );
  NT2_TEST( !nt2::isulpequal( T(1),  nt2::ones(1, 2, tgt)) );
  NT2_TEST(  nt2::isulpequal( nt2::ones(1, 1, tgt) , T(1)) );
  NT2_TEST( !nt2::isulpequal( nt2::ones(1, 2, tgt) , T(1)) );
  NT2_TEST(  nt2::isulpequal( nt2::Nan<T>(), nt2::nan(1, 1, tgt)) );
  NT2_TEST( !nt2::isulpequal( nt2::Nan<T>(), nt2::nan(1, 2, tgt)) );
}
