/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isequal function"

#include <nt2/include/functions/isequal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE( fundamental_isequal )
{
  NT2_TEST( nt2::isequal('e', 'r') );
  NT2_TEST( nt2::isequal(1, 2)   );
  NT2_TEST( nt2::isequal(1., 2)  );
  NT2_TEST( nt2::isequal(1.f, 2.0) );
}

NT2_TEST_CASE( container_isequal )
{
  using nt2::_; 
  nt2::table<short int> a = nt2::ones(4, nt2::meta::as_<short int>());
  nt2::table<short int> b = nt2::ones(4, nt2::meta::as_<short int>());
  disp("a", a);
  disp("b", b);
  NT2_TEST( nt2::isequal( a, b)       );
  b(3, 3) = 2; 
  NT2_TEST( !nt2::isequal( a, b)       );
    NT2_TEST( nt2::isequal( nt2::ones(4)      ,nt2::ones(4))       );
//   NT2_TEST( nt2::isequal( nt2::ones(4,1)    ,nt2::ones(4,1))     );
//   NT2_TEST( nt2::isequal( nt2::ones(4,1,1)  ,nt2::ones(4,1,1))   );
//   NT2_TEST( nt2::isequal( nt2::ones(4,1,4,1),nt2::ones(4,1,4,1)) );
  
//   NT2_TEST( !nt2::isequal( nt2::ones(2,3)    , nt2::ones(4))          );
//   NT2_TEST( !nt2::isequal( nt2::ones(4,1)    , nt2::zeros(4,1))       );
//   NT2_TEST( !nt2::isequal( nt2::ones(3,3,1,9), nt2::ones(3, 3, 1, 9)) );
  
}
