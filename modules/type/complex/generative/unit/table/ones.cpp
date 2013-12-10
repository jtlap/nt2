//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( ones, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::meta::as_;
  nt2::table< cT > x0 = nt2::ones( as_<cT>() );

  NT2_TEST_EQUAL( x0(1), nt2::One<cT>() );

  nt2::table<cT> ref( nt2::of_size(8,8) );
  for(int j=1;j<= 8;++j)
    for(int i=1;i<= 8;++i)
      ref(i,j) = nt2::One<cT>();

  nt2::table<cT> x1 = nt2::ones(nt2::of_size(8, 8), as_<cT>() );

  NT2_TEST_EQUAL(x1,ref);

  nt2::table<cT> x2 = nt2::ones(8, 8, as_<cT>() );
  NT2_TEST_EQUAL(x2,ref);

  nt2::table<cT> x3 = nt2::ones(8, as_<cT>() );
  NT2_TEST_EQUAL(x3,ref);
}


