//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::memory composite container"

#include <nt2/table.hpp>
#include <nt2/core/functions/of_size.hpp>

#include <complex>
#include <nt2/sdk/complex/complex.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE( composite_table )
{
  using nt2::settings;
  using nt2::table;
  using nt2::of_size;

  table< std::complex<float> > x( of_size(2,3) );
  x = x + x;
  std::cout << x(1) << "\n";
}
