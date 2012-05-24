//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II       
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI       
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#define NT2_UNIT_MODULE "nt2 optimize toolbox - hjmin"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of optimize components
//////////////////////////////////////////////////////////////////////////////
#include <nt2/include/functions/hjmin.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <iostream>

void f1d(double& y, const nt2::table<double>& x )    {
  //  double z = x(nt2::first_index<0>(x));
  double z = x(1); 
  y = nt2::sqr(x(1)+4.0)+nt2::sqr(x(2)+1.0); 
  //y(1) = x(1)*x(1)*x(1)-3*x(1)+4;
}
// void f1f(nt2::table<float>& y, const nt2::table<float>& x )    {
//   y(1) = x(1)*x(1)*x(1)-3*x(1)+4;
// }

NT2_TEST_CASE_TPL ( hjmind, (double)) 
{   
  using nt2::hjmin;
  using nt2::table;
  typedef table < double> table_t; 
  table_t  b =  repnum(3.0, nt2::of_size(2, 1));
  table_t  h =  repnum(0.2, nt2::of_size(2, 1));     
  hjmin < table_t > hjm;
  hjm.optimize(&f1d, b, h); 
  std::cout << "minimum " << hjm.getMinimum(); 
  std::cout << " at point (" <<  double(b(1)) << ", " << double(b(2)) <<")";
  std::cout << " in " << hjm.getNbIteration() << " iterations" << std::endl;
}

// NT2_TEST_CASE_TPL ( hjmind, (float)) 
// {   
//   using nt2::hjmin;
//   matrix < float >  b =  3*ones(1);
//   matrix < float >  h =  0.2*ones(1); 
//   hjmin < matrix < float > > hjm;
//   hjm.optimize(&f1, b, h); 
//   cout << "minimum " << hjm.getMinimum(); 
//   cout << " au point " <<  b;
//   cout << " en " << hjm.getNbIteration() << " iterations" << endl; 
// }
