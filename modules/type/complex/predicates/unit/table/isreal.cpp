/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::isreal function for complex tables"

#include <nt2/table.hpp>
#include <nt2/include/functions/isreal.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/constants/nan.hpp>

NT2_TEST_CASE( scalar_isreal_cplx )
{
  typedef std::complex<float> cT;
  cT a = cT(1);

  NT2_TEST( nt2::isreal( a) );
  a = cT(0, 1);
  NT2_TEST( !nt2::isreal( a) );
}


NT2_TEST_CASE( container_isreal_cplx )
{
  typedef std::complex<float> cT;
  nt2::table<cT> a = nt2::ones(4, nt2::meta::as_<cT>());

  NT2_TEST( nt2::isreal( a) );
  a(2, 2) = cT(0, 1);
  NT2_TEST( !nt2::isreal( a) );
}
