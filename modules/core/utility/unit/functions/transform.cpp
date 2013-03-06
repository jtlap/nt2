//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2::transform function"

#include <nt2/table.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/transform.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( direct_transform, (double) )
{
  nt2::table<T> out( nt2::of_size(5,7) );
  nt2::table<T> in = nt2::ones( nt2::of_size(5,7), nt2::meta::as_<T>() );

  nt2::transform(out, in+in);

  for(std::size_t i=1;i<=nt2::numel(out);++i)
    NT2_TEST_EQUAL(out(i), in(i)+in(i));

  NT2_DISPLAY(out);
}

NT2_TEST_CASE_TPL( partial_transform, (double) )
{
  nt2::table<T, nt2::_1D> out = nt2::zeros( nt2::of_size(21), nt2::meta::as_<T>() );
  nt2::table<T, nt2::_1D> in  = nt2::ones( nt2::of_size(21), nt2::meta::as_<T>() );

  nt2::transform(out,in+in,6,6);

  for(std::size_t i=1;i<=6;++i)
    NT2_TEST_EQUAL(out(i), T(0));

  for(std::size_t i=7;i<=12;++i)
    NT2_TEST_EQUAL(out(i), in(i)+in(i));

  for(std::size_t i=13;i<=nt2::numel(out);++i)
    NT2_TEST_EQUAL(out(i), T(0));

  NT2_DISPLAY(out);
}
