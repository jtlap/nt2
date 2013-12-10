//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/falses.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL( falses, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  typedef nt2::logical<T> lT;
  typedef nt2::logical<cT> lcT;
  using nt2::meta::as_;
  nt2::table<lcT> x1 = nt2::falses( as_< nt2::logical<cT> >() );

  NT2_TEST_EQUAL( x1(1), false );
  nt2::table<lcT> x2 = nt2::falses( 2, 3, as_<lcT>() );
  NT2_TEST_EQUAL( x2, nt2::falses(2, 3, as_<lT>()));
  nt2::table<lcT> x3 = nt2::falses( 2, 3, 4, as_<lcT>() );
  NT2_TEST_EQUAL( x3, nt2::falses(2, 3, 4, as_<lT>()));
}

