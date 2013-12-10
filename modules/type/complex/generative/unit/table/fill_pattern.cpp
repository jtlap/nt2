//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/fill_pattern.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/constants/i.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>


NT2_TEST_CASE_TPL( fill_pattern, NT2_REAL_TYPES )
{
  using nt2::meta::as_;
  using nt2::meta::value_type_;
  typedef std::complex<T> cT;

  nt2::table<cT> x  = nt2::_(T(1),T(3))+nt2::I<cT>()*nt2::_(T(-3),T(-1));
  nt2::table<cT> ref;

  nt2::table<cT> x1 = nt2::fill_pattern(x, nt2::of_size(0) );
  NT2_TEST( nt2::isempty(x1) );

  ref.resize( nt2::of_size(5) );
  for(std::size_t i=1;i<=5;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<cT> x2 = nt2::fill_pattern(x, nt2::of_size(5) );
  NT2_TEST_EQUAL( x2, ref );

  ref.resize( nt2::of_size(5,5) );
  for(std::size_t i=1;i<=25;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<cT> x3 = nt2::fill_pattern(x, nt2::of_size(5,5) );
  NT2_TEST_EQUAL( x3, ref );

  ref.resize( nt2::of_size(5,5,5) );
  for(std::size_t i=1;i<=125;++i) ref(i) = x(1+(i-1)%3);

  nt2::table<cT> x4 = nt2::fill_pattern(x, nt2::of_size(5,5,5) );
  NT2_TEST_EQUAL( x4, ref );
}
