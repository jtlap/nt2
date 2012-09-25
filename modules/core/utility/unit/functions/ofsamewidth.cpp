/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::ofsamewidth function"

#include <nt2/table.hpp>
#include <nt2/include/functions/ofsamewidth.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE( fundamental_ofsamewidth )
{
  NT2_TEST( nt2::ofsamewidth('f', 'f') );
  NT2_TEST( nt2::ofsamewidth(1, 1)   );
  NT2_TEST( nt2::ofsamewidth(1., 1.)  );
  NT2_TEST( nt2::ofsamewidth(1.f, 1.f) );

  NT2_TEST( nt2::ofsamewidth('e', 'r') );
  NT2_TEST( nt2::ofsamewidth(1, 2)   );
  NT2_TEST( nt2::ofsamewidth(1., 2.)  );
  NT2_TEST( nt2::ofsamewidth(1.f, 2.0f) );
  NT2_TEST( nt2::ofsamewidth(nt2::Nan<float>(), nt2::Nan<float>())); 
}

NT2_TEST_CASE( container_ofsamewidth )
{
  using nt2::_;
  nt2::table<float> a = nt2::ones(4, nt2::meta::as_<float>());
  nt2::table<float> b = nt2::ones(4, 3, nt2::meta::as_<float>());

  NT2_TEST( !nt2::ofsamewidth( a, b) );
  b = nt2::ones(3, 4, nt2::meta::as_<float>());
  NT2_TEST( nt2::ofsamewidth( a, b) );

}
