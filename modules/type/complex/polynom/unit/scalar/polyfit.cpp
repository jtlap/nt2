//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - polyfit/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
/// 
#include <nt2/include/functions/polyfit.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/polyval.hpp>
#include <nt2/include/functions/isulpequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tie.hpp>

#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( plevl_real__4_0,  NT2_REAL_TYPES)
{
  
  using nt2::polyfit;
  using nt2::tag::polyfit_;
  typedef std::complex<T> cT; 
  cT a [] = {0.0, 1.0, 2.0, 3.0,  4.0,  5.0};
  cT b [] = {0.0, 0.8, 0.9, 0.1, -0.8, -1.0};
  nt2::table<cT> x(nt2::of_size(1,6));
  nt2::table<cT> y(nt2::of_size(1,6));
  
 for(int i=0; i < 6; ++i)
   {
     x(i+1) = cT(a[i]);
     y(i+1) = cT(b[i]); 
   }
  NT2_DISPLAY(x);
  NT2_DISPLAY(y);
  nt2::table<cT> z = polyfit(x, y, 3);
   NT2_DISPLAY(z);  
} // end of test for floating_

