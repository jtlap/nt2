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
#include <nt2/include/functions/ones.hpp> // no worky
#include <nt2/include/functions/cos.hpp>

#include <complex>
#include <nt2/sdk/complex/complex.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

//==============================================================================
// Test for container default ctor
//==============================================================================
NT2_TEST_CASE( composite_table )
{
  using nt2::table;
  using nt2::of_size;
  using nt2::settings;

  table< std::complex<float> > y,x( of_size(2,3) );
  NT2_DISPLAY(x);

  for(std::size_t i=1;i<=6;++i)
  {
    x(i) = std::complex<float>(1.f/i,i-1.f);
  }

  NT2_DISPLAY(x(1)+x(2));

  y = -x;
  NT2_DISPLAY(y);

  y = cos(x);
  NT2_DISPLAY(y);

  y = -(-x);
  NT2_DISPLAY(y);

  y = x + x;
  NT2_DISPLAY(y);

  y = x + x + x;
  NT2_DISPLAY(y);

  y = x * 3.f ;
  NT2_DISPLAY(y);
}
