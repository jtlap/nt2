//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/cic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>


NT2_TEST_CASE_TPL(cic0, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  {
    nt2::table<cT> ref( nt2::of_size(3,1) );
    for(int i=1;i<= 3;++i)
      ref(i) = cT(0);

    nt2::table<cT> x0 = nt2::cic(3, 1, nt2::meta::as_<cT>());
    nt2::table<cT> x1 = nt2::cic(3, 1, nt2::meta::as_<T>());

    NT2_TEST_EQUAL( x0,ref );
    NT2_TEST_EQUAL( x1,ref );
  }
   {
    nt2::table<cT> ref( nt2::of_size(1,3) );
    for(int i=1;i<= 3;++i)
      ref(1, i) = cT(i-1);

    nt2::table<cT> x0 = nt2::cic(1, 3, nt2::meta::as_<cT>());
    nt2::table<cT> x1 = nt2::cic(1, 3, nt2::meta::as_<T>());

    NT2_TEST_EQUAL( x0,ref );
    NT2_TEST_EQUAL( x1,ref );
  }
}

NT2_TEST_CASE_TPL(cic1, NT2_REAL_TYPES)
{
  {
    typedef std::complex<T> cT;
    nt2::table<cT> ref( nt2::of_size(3,2) );
    for(int i=1;i<= 3;++i)
      for(int j=1;j<= 2;++j)
        ref(i,j) = cT(j-1);

    nt2::table<cT> x0 = nt2::cic(3, 2, nt2::meta::as_<cT>());
    nt2::table<cT> x1 = nt2::cic(3, 2, nt2::meta::as_<T>());

    NT2_TEST_EQUAL( x0,ref );
    NT2_TEST_EQUAL( x1,ref );
  }
  {
    typedef std::complex<T> cT;
    nt2::table<cT> ref( nt2::of_size(2, 3) );
    for(int i=1;i<= 2;++i)
      for(int j=1;j<= 3;++j)
        ref(i,j) = cT(j-1);

    nt2::table<cT> x0 = nt2::cic(2, 3, nt2::meta::as_<cT>());
    nt2::table<cT> x1 = nt2::cic(2, 3, nt2::meta::as_<T>());

    NT2_TEST_EQUAL( x0,ref );
    NT2_TEST_EQUAL( x1,ref );
  }
}

NT2_TEST_CASE_TPL(cic2, NT2_REAL_TYPES)
{
  typedef std::complex<T> cT;
  nt2::table<cT> ref( nt2::of_size(3,2,3) );
  for(int i=1;i<= 3;++i)
    for(int j=1;j<= 2;++j)
      for(int k=1;k<= 3;++k)
        ref(i,j, k) = cT(j-1);

  nt2::table<cT> x0 = nt2::cic(3, 2, 3, nt2::meta::as_<cT>());
  nt2::table<cT> x1 = nt2::cic(3, 2, 3, nt2::meta::as_<T>());

  NT2_TEST_EQUAL( x0,ref );
  NT2_TEST_EQUAL( x1,ref );
}

