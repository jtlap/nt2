/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::splat"

#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test splat
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(splat, NT2_TYPES)
{
  using nt2::tag::splat_;
  using boost::is_same;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<splat_(int,nt2::meta::as_<T>)>::type
                            , T
                            >::value
            )
          );

  NT2_TEST_EQUAL( nt2::splat<T>(42), T(42));
}
