//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/logspace.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/exp10.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL( logspace, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  {

    nt2::table<cT> ref = nt2::exp10(nt2::linspace(cT(0, 1),cT(0, 4),10));
    nt2::table<cT> x = nt2::logspace(cT(0, 1),cT(0, 4), 10);
    NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,10) );
    NT2_TEST_ULP_EQUAL( x, ref, 1 );
  }
  {
    nt2::table<cT> ref = nt2::exp10(nt2::linspace(cT(0),cT(1),50));
    nt2::table<cT> x = nt2::logspace(cT(0),cT(1));
    NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,50) );
    NT2_TEST_ULP_EQUAL( x, ref, 1 );

    ref = nt2::exp10(nt2::linspace(cT(1),cT(0),50));
    nt2::table<cT> xr = nt2::logspace(cT(1),cT(0));
    NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,50) );
    NT2_TEST_ULP_EQUAL( xr, ref, 1 );
  }

}

NT2_TEST_CASE_TPL( logspace_with_size, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;

  nt2::table<cT> ref = nt2::exp10(nt2::linspace(T(0),T(1),7));

  nt2::table<cT> x = nt2::logspace(cT(0),cT(1),7);
  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,7) );
  NT2_TEST_ULP_EQUAL( x, ref, 1 );

  ref = nt2::exp10(nt2::linspace(cT(1),cT(0),7));
  nt2::table<cT> xr = nt2::logspace(cT(1),cT(0),7);
  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,7) );
  NT2_TEST_ULP_EQUAL( xr, ref, 1 );
}

NT2_TEST_CASE_TPL( logspace_pi, NT2_REAL_TYPES )
{
  typedef std::complex<T> cT;
  nt2::table<cT> x = nt2::logspace(cT(2),nt2::Pi<cT>(),7);
  nt2::table<cT> ref = nt2::exp10(nt2::linspace(cT(2),nt2::Log10_pi<cT>(), 7));

  NT2_TEST_EQUAL( x.extent(), nt2::of_size(1,7 ) );
  NT2_TEST_ULP_EQUAL( x, ref, 1 );

  nt2::table<cT> xr = nt2::logspace(cT(2),nt2::Pi<cT>(),7, nt2::regular_);
  ref = nt2::exp10(nt2::linspace(cT(2),nt2::Pi<cT>(), 7));

  NT2_TEST_EQUAL( xr.extent(), nt2::of_size(1,7 ) );
  NT2_TEST_ULP_EQUAL( xr, ref, 1 );

  nt2::table<cT> xd1 = nt2::logspace(cT(2),nt2::Pi<cT>(),1, nt2::regular_);
  nt2::table<cT> xd2 = nt2::logspace(cT(2),nt2::Pi<cT>(),1);
  NT2_TEST_EQUAL( xd1.extent(), nt2::of_size(1,1 ) );
  NT2_TEST_EQUAL( xd2.extent(), nt2::of_size(1,1 ) );

  NT2_TEST_ULP_EQUAL( xd1(1), nt2::exp10(nt2::Pi<cT>()), 1 );
  NT2_TEST_ULP_EQUAL( xd2(1), nt2::Pi<cT>(), 1);
}
