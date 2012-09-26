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
#include <nt2/include/functions/ones.hpp>

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

  table< std::complex<float> > x( of_size(2,3) );

  // assign in complex is ambiguous/missing for dry
//  x = nt2::ones(2,3, nt2::meta::as_< std::complex<float> >() );
  NT2_DISPLAY(x);

  // fusion::vector(T&) <= T const& seems to not be supported
  x(2) = std::complex<float>(-8.54f,1.f);

  NT2_DISPLAY(x);

  for(std::size_t i=1;i<=6;++i)
  {
    std::complex<float> y(1.f/i,i-1.f);
    x(i) = y;
  }

  NT2_DISPLAY(x);

  x = x + x;

// non worky
//  x = x + x + x;

  NT2_DISPLAY(x);
}
