//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 linalg toolbox - tied svd_solve function"

#include <nt2/table.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp> 
#include <nt2/include/functions/svd_solve.hpp>
#include <nt2/include/functions/tie.hpp>

#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

NT2_TEST_CASE_TPL ( svd_solve_expr, NT2_REAL_TYPES)
{
  typedef typename nt2::meta::as_integer<T, signed>::type itype_t; 
  typedef nt2::table<T> t_t;
  typedef nt2::table<itype_t> it_t; 

  T bc[25] =  {
    1.0, 2.0, 0., 0., 0.,
    0. , 2.0, 0., 0., 0., 
    1.,  100.,  10000., 4., 0.2, 
    .01,  1.,  100., 0.2, 0.1,
    .0001,  .01,  1., 0., 0.000
  };
  
  int k = 0;
  t_t a(nt2::of_size(5, 5)); 
  for(int i=1; i <= 5; i++)
    {
      for(int j=1; j <= 5; j++)
        {
          a(i, j) = bc[k++]; 
        }
      
    }
  NT2_DISP(a);
  t_t x, b =  nt2::ones(5, 1, nt2::meta::as_<T>());
  NT2_DISP(b);
  int32_t rank; 
  nt2::tie(x, rank) = nt2::svd_solve(a, b);
  NT2_DISP(x);
  std::cout << rank<< std::endl;

}
