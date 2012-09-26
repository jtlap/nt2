//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - orth basis of image"

#include <nt2/table.hpp>
#include <nt2/include/functions/orth.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <nt2/sdk/meta/type_id.hpp>

NT2_TEST_CASE_TPL(orth, NT2_REAL_TYPES)
{
  typedef T r_t;
  using nt2::orth;
  using nt2::tag::orth_;
  std::cout << std::setprecision(20); 
  nt2::table<T> n = nt2::eye(10, 10, nt2::meta::as_<T>());
  n(3, 5) = T(2);
  n(4, 4) = T(0);
  n(1, 1) = 5*nt2::Eps<T>();
  nt2::table<T> orthn = nt2::orth(n);
  NT2_DISPLAY(n);
  NT2_DISPLAY(orthn);
  nt2::table<T> orthn1 = nt2::orth(n,  100*nt2::Eps<T>());
  NT2_DISPLAY(orthn1);
  T rn[100] = {
    0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, 1, 0, 0, 0, 0, 0, 
    0.92387953251128673848, 0, -0, 0, 0, 0, 0, -0.38268343236508972627, 
    0, 0, -0, 0, 0, 0, 0, 0, 
    0.38268343236508972627, 0, -0, 0, 0, 0, 0, 0.92387953251128673848, 
    -0, 0, -0, 0, 0, 1, 0, 0, 
    -0, 0, -0, 0, 0, -0, 1, 0, 
    -0, 0, -0, 1, 0, -0, -0, 0, 
    -0, 1, -0, -0, 0, -0, -0, 0, 
    -0, -0, -0, -0, 1, -0, -0, 0
  };
  int k = 0;
  nt2::table<T> a(nt2::of_size(10, 8));
  for(int i=1; i <= 10; i++)
    {
      for(int j=1; j <= 8; j++)
        {
          a(i, j) = rn[k++];
        }
    }
   NT2_DISPLAY(orthn1-a);
  NT2_TEST(nt2::isulpequal(a, orthn1, T(1.0)));
  //  std::cout << nt2::type_id(a(nt2::_, 1)) << std::endl;
  std::cout << nt2::type_id(  nt2::_)     << std::endl;  
}
