/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isreal function"

#include <nt2/table.hpp>
#include <nt2/include/functions/isreal.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE( fundamental_isreal )
{
  NT2_TEST( (nt2::isreal('f')) );
  NT2_TEST( (nt2::isreal(1))   );
  NT2_TEST( (nt2::isreal(1.))  );
  NT2_TEST( (nt2::isreal(1.f)) );

  NT2_TEST( nt2::isreal(nt2::Nan<float>()));
}

NT2_TEST_CASE( container_isreal )
{
  using nt2::_;
  nt2::table<float> a = nt2::ones(4, nt2::meta::as_<float>());

  NT2_TEST( nt2::isreal( a) );
}
