/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2::issymetric function"

#include <nt2/table.hpp>
#include <nt2/include/functions/issymetric.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE( fundamental_issymetric )
{
  NT2_TEST( nt2::issymetric('e') );
  NT2_TEST( nt2::issymetric(1)   );
  NT2_TEST( nt2::issymetric(1.)  );
  NT2_TEST( nt2::issymetric(1.f) );
}

 NT2_TEST_CASE( container_issymetric )
 {
   NT2_TEST( nt2::issymetric( nt2::ones(4, nt2::meta::as_<float>()))      );
   NT2_TEST( nt2::issymetric( nt2::ones(4,4))     );
   
   NT2_TEST( !nt2::issymetric( nt2::ones(4,1,1))   );
   NT2_TEST( !nt2::issymetric( nt2::ones(4,1,1,1)) );
   
   NT2_TEST( !nt2::issymetric( nt2::ones(2,3))     );
   NT2_TEST( !nt2::issymetric( nt2::ones(3,1,2))   );
   NT2_TEST( !nt2::issymetric( nt2::ones(3,3,1,9)) );
   
 }
NT2_TEST_CASE( table_issymetric )
{
  nt2::table<float> a(nt2::of_size(3, 3));

  for(std::ptrdiff_t i=1; i <= 3; i++)
    {
      for(std::ptrdiff_t j=1; j <= 3; j++)
        {
          a(i, j) =  float(i+j); 
        }
    }
  for(std::ptrdiff_t i=1; i <= 3; i++)
    {
      for(std::ptrdiff_t j=1; j <= 3; j++)
        {
          std::cout << a(i, j) << "    ";  
        }
      std::cout << std::endl; 
    }
  
  NT2_TEST( nt2::issymetric(a)     );
  a(1, 2) = 25.0f; 
  for(std::ptrdiff_t i=1; i <= 3; i++)
    {
      for(std::ptrdiff_t j=1; j <= 3; j++)
        {
          std::cout << a(i, j) << "    ";  
        }
      std::cout << std::endl; 
    }
  NT2_TEST( !nt2::issymetric(a)     );
  
  
  nt2::table<float> b;
  b =  nt2::ones(3, 4, nt2::meta::as_<float>()); 
  NT2_TEST( !nt2::issymetric(b)     );
  
  
}

