//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - polyval/scalar Mode" 

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynomials components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
/// 
#include <nt2/toolbox/polynomials/include/functions/polyval.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/polyfit.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>

#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( polyval_real__1_0,  NT2_REAL_TYPES)
{ 
  
  using nt2::polyval;
  using nt2::tag::polyval_;
  nt2::table<T> x =  nt2::_(T(1), T(4));
  nt2::table<T> p =  nt2::_(T(1), T(4));
  NT2_DISPLAY(polyval(p, T(1))); 
  NT2_TEST_EQUAL(polyval(p, T(1)), T(10));
  NT2_TEST_EQUAL(polyval(p, T(2)), T(26));
  
  NT2_DISPLAY(polyval(p, nt2::_(T(1), T(4))));
} // end of test for floating_


NT2_TEST_CASE_TPL ( polyval_real__2_0,  NT2_REAL_TYPES)
{ 
  using nt2::polyfit;
  using nt2::tag::polyfit_;
  nt2::table<T> x =  nt2::reshape(nt2::_(T(1), T(4)), nt2::of_size(2, 2));
  nt2::table<T> p =  nt2::_(T(1), T(3));
  std::cout << 0 << std::endl; 
  nt2::table<T> y =  nt2::polyval(p, x);
  y(nt2::end_) = T(26); 
  std::cout << 1 << std::endl;  
  nt2::table<T> r; 
  size_t df; 
  T normr;     
  nt2::table<T> mu; 
  nt2::tie(p, r, df, normr, mu) = polyfit(x, y, 2); 
  std::cout << 2 << std::endl; 
  NT2_DISPLAY(p);
  NT2_DISPLAY(r);  
  NT2_DISPLAY(df);
  NT2_DISPLAY(normr);  
  NT2_DISPLAY(mu);
  NT2_DISPLAY(polyval(p, (x-mu(1))/mu(2))); 
  NT2_DISPLAY(polyval(p, x, mu));  
  nt2::table<T> delta; 
  nt2::table<T> xx =  nt2::reshape(nt2::_(T(1), T(0.5), T(4.5)), 2, 4);
//  y = polyval(p, xx, r, df, normr, mu);
  NT2_DISPLAY(y); 
  tie(y, delta) = polyval(p, xx, r, df, normr);   
  NT2_DISPLAY(y); 
  NT2_DISPLAY(delta); 
} // end of test for floating_


// NT2_TEST_CASE_TPL ( polyval_real__3_0,  NT2_REAL_TYPES)
// { 
//   using nt2::polyfit;
//   using nt2::tag::polyfit_;
//   nt2::table<T> x =  nt2::_(T(1), T(4));
//   nt2::table<T> p =  nt2::_(T(1), T(3));
//   std::cout << 0 << std::endl; 
//   nt2::table<T> y =  nt2::polyval(p, x); 
//   std::cout << 1 << std::endl; 
//   nt2::table<T> r;
//   T df, normr;
//   nt2::table<T> mu;
//   nt2:: polyfit_infos<T> s; 
//   nt2::tie(p, s) = polyfit(x, y);
//   std::cout << 2 << std::endl; 
//   NT2_DISPLAY(p);
//   NT2_DISPLAY(s.r); 
//   NT2_DISPLAY(s.df);
//   NT2_DISPLAY(s.normr);
// //   NT2_DISPLAY(mu);
// //   NT2_DISPLAY(polyval(p, (x-mu(1))/mu(2)));
// //   NT2_DISPLAY(polyval(p, x, mu)); 
// //   nt2::table<T> delta;
// //   nt2::table<T> xx =  nt2::_(T(1), T(0.5), T(4));  
// //   tie(y, delta) = polyval(p, xx, r, df, normr, mu); 
// //   NT2_DISPLAY(y);
// //   NT2_DISPLAY(delta); 
// } // end of test for floating_

