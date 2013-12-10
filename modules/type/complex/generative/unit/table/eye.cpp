//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/complexify.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( eye, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  using nt2::meta::as_;
  nt2::table<cT> x1 = nt2::eye( as_<cT>() );
  NT2_TEST_EQUAL( x1, nt2::ones(1, as_<cT>()) );
  nt2::table<cT> x2 = nt2::eye( 2, 3, as_<cT>() );
  NT2_TEST_EQUAL( x2, nt2::complexify(nt2::eye(2, 3, as_<T>())));
}
