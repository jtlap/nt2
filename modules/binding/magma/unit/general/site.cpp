//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/magma/magma.hpp>
#include <magma.h>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/meta/type_id.hpp>

#include <iostream>

NT2_TEST_CASE( default_site )
{
  typedef boost::dispatch::default_site<void>::type current_default_site;

  std::cout << nt2::type_id<current_default_site>() << "\n";
}
