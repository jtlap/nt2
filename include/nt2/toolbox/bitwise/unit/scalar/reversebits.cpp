//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - unit/scalar Mode"

#include <nt2/toolbox/bitwise/include/reversebits.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <iostream>
//////////////////////////////////////////////////////////////////////////////
// Test behavior of bitwise components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( reversebits, NT2_INTEGRAL_TYPES
                  )
{
  using nt2::reversebits; 
  using nt2::tag::reversebits_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<reversebits_(T)>::type
           , T
              >::value)
           );
  NT2_TEST_EQUAL(reversebits(T(-1)),  T(-1)); 
  NT2_TEST_EQUAL(reversebits(T(0)), 0);
  NT2_TEST_EQUAL(reversebits(T(1)), T(1ull << sizeof(T)*8-1));
  std::cout << std::hex << reversebits(T(1)) << "  " << nt2::Signmask<T>() << std::endl; 
}
