//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/table.hpp>
#include <nt2/include/functions/size.hpp>
#include <nt2/include/functions/indices.hpp>
#include <nt2/include/functions/resize.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>
#include <boost/dispatch/meta/nth_hierarchy.hpp>


NT2_TEST_CASE_TPL( indices, NT2_TYPES )
{
  using nt2::meta::as_;
  typedef std::complex<T> cT;
  {
    for(std::ptrdiff_t i=-1;i<2;++i)
    {
      nt2::table<cT> x1 = nt2::indices( nt2::over(1,i), as_<cT>() );
      NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(1) );
      NT2_TEST_EQUAL( x1(1),T(i) );
    }
  }
  {
    for(std::ptrdiff_t base=-1;base<2;++base)
    {
      nt2::table<T> ref( nt2::of_size(3,3) );
      for(int j=0;j< 3;++j)
        for(int i=0;i< 3;++i)
          ref(1+i,1+j) = i+base;

      nt2::table<cT> x0 = nt2::indices(3, nt2::over(1,base), as_<T>());
      NT2_TEST_EQUAL( x0,ref );

      for(int j=0;j< 3;++j)
        for(int i=0;i< 3;++i)
          ref(1+i,1+j) = j+base;

      x0 = nt2::indices(3, nt2::over(2,base), as_<T>());
      NT2_TEST_EQUAL( x0,ref );
    }
  }
  {
    for(std::ptrdiff_t base=-1;base<2;++base)
    {
      nt2::table<cT> ref( nt2::of_size(3,4) );
      for(int j=0;j< 4;++j)
        for(int i=0;i< 3;++i)
          ref(1+i,1+j) = i+base;

      nt2::table<cT> x0 = nt2::indices(3,4, nt2::over(1,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x0), nt2::of_size(3,4) );
      NT2_TEST_EQUAL( x0,ref );

      nt2::table<cT> x0f = nt2::indices( nt2::of_size(3,4), nt2::over(1,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x0f), nt2::of_size(3,4) );
      NT2_TEST_EQUAL( x0f,ref );

      for(int j=0;j< 4;++j)
        for(int i=0;i< 3;++i)
          ref(1+i,1+j) = j+base;

      nt2::table<cT> x1 = nt2::indices(3,4, nt2::over(2,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x1), nt2::of_size(3,4) );
      NT2_TEST_EQUAL( x1,ref );

      nt2::table<cT> x1f = nt2::indices( nt2::of_size(3,4), nt2::over(2,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x1f), nt2::of_size(3,4) );
      NT2_TEST_EQUAL( x1f,ref );

      ref.resize( nt2::of_size(3,3,3) );
      for(int k=0;k< 3;++k)
        for(int j=0;j< 3;++j)
          for(int i=0;i< 3;++i)
            ref(1+i,1+j,1+k) = k+base;

      nt2::table<cT> x2 = nt2::indices(3, 3,3, nt2::over(3,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x2), nt2::of_size(3,3,3) );
      NT2_TEST_EQUAL( x2,ref );

      nt2::table<cT> x2f = nt2::indices( nt2::of_size(3,3,3), nt2::over(3,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x2f), nt2::of_size(3,3,3) );
      NT2_TEST_EQUAL( x2f,ref );

      ref.resize( nt2::of_size(3,3,3,3) );
      for(int l=0;l< 3;++l)
        for(int k=0;k< 3;++k)
          for(int j=0;j< 3;++j)
            for(int i=0;i< 3;++i)
              ref(1+i,1+j,1+k,1+l) = l+base;

      nt2::table<cT> x3 = nt2::indices(3,3,3,3, nt2::over(4,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x3), nt2::of_size(3,3,3,3) );
      NT2_TEST_EQUAL( x3,ref );

      nt2::table<cT> x3f = nt2::indices( nt2::of_size(3,3,3,3), nt2::over(4,base), as_<cT>());
      NT2_TEST_EQUAL( nt2::extent(x3f), nt2::of_size(3,3,3,3) );
      NT2_TEST_EQUAL( x3f,ref );
    }
  }
}
