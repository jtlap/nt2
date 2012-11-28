/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::issorted function"

#include <nt2/table.hpp>
#include <nt2/include/functions/issorted.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE( fundamental_issorted )
{
  NT2_TEST( nt2::issorted('f') );
  NT2_TEST( nt2::issorted(1)   );
  NT2_TEST( nt2::issorted(1.)  );
  NT2_TEST( nt2::issorted(1.f)  );
  NT2_TEST( nt2::issorted(nt2::Nan<float>()));
}

NT2_TEST_CASE( container_issorted )
{
  using nt2::_;
  nt2::table<float> a = nt2::_(1.0f, 10.0f);


  NT2_TEST( nt2::issorted( a) );
  NT2_TEST( !nt2::issorted( a, false));
  NT2_TEST( nt2::issorted( a, true));

  a =  nt2::rif(3, 4, nt2::meta::as_<float>());
  NT2_TEST( nt2::issorted( a) );
  NT2_TEST( !nt2::issorted( a, false));
  NT2_TEST( nt2::issorted( a, true));
  NT2_TEST( !nt2::issorted( a, 1, false));
  NT2_TEST( nt2::issorted( a, 1, true));
  NT2_TEST(! nt2::issorted( a, 2, false));
  NT2_TEST( nt2::issorted( a, 2, true));
  NT2_TEST( !nt2::issorted( a, 3, false));
  NT2_TEST( nt2::issorted( a, 3, true));


}
