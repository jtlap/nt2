//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/isband.hpp>
#include <nt2/include/functions/band.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/table.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_isband )
{
  NT2_TEST( nt2::isband('e', 0, 0) );
  NT2_TEST( nt2::isband(1, 0, 0)   );
  NT2_TEST( nt2::isband(1., 0, 0)  );
  NT2_TEST( nt2::isband(1.f, 0, 0) );
}

NT2_TEST_CASE( container_isband )
{
  nt2::table<double > a =  nt2::eye(4);
  NT2_TEST( !nt2::isband(a, 1, 1));
}

NT2_TEST_CASE_TPL(bandwidth1, NT2_REAL_TYPES)
{
  using nt2::bandwidth;
  using nt2::band;
  nt2::table<T> n = nt2::ones(4, 7, nt2::meta::as_<T>());

 for(int i=-2; i <3 ; i++)
 {
   for(int j=i; j < 6; j++)
   {
     nt2::container::table<T> a = band(n, i, j);
     auto r = bandwidth(a);
     int l = boost::fusion::at_c<0>(r);
     int u = boost::fusion::at_c<1>(r);
     NT2_TEST(isband(a, l, u));
     NT2_TEST(!isband(a, l+1, u));
     NT2_TEST(!isband(a, l,  u-1));
   }
 }
}

