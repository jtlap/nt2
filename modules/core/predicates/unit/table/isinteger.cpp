/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isinteger function"

#include <nt2/include/functions/isinteger.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_isinteger )
{
  NT2_TEST( nt2::isinteger('e') );
  NT2_TEST( nt2::isinteger(1)   );
  NT2_TEST( !nt2::isinteger(1.)  );
  NT2_TEST( !nt2::isinteger(1.f) );
}

NT2_TEST_CASE( container_isinteger )
{
  NT2_TEST( nt2::isinteger( nt2::ones(4, nt2::meta::as_<char > ()))       );
  NT2_TEST( nt2::isinteger( nt2::ones(4,1, nt2::meta::as_<int > ()))     );
  NT2_TEST( !nt2::isinteger( nt2::ones(4,1,1, nt2::meta::as_<float > ()))   );

}
