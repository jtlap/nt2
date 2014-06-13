//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/center.hpp>
#include <nt2/include/constants/nan.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( center, (float)(double))
{
  T x = nt2::center(T(42));
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::center(T(42),1);
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::center(T(42),0);
  NT2_TEST_EQUAL( x, T(0) );

  x = nt2::center(nt2::Nan<T>(),1);
  NT2_TEST_EQUAL( x, nt2::Nan<T>() );
}
