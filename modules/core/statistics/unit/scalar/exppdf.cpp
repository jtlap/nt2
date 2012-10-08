//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 statistics toolbox - exppdf/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of statistics components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 22/02/2011
/// 
#include <nt2/include/functions/exppdf.hpp>
#include <nt2/include/functions/bsxfun.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/constants/invexp_1.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>  
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/table.hpp>

NT2_TEST_CASE_TPL ( exppdf_1,  (float))//NT2_REAL_TYPES)
{
  
  using nt2::exppdf;
  using nt2::tag::exppdf_;
  using nt2::_; 
  

  // specific values tests
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Nan<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::One<T>()),  nt2::Invexp_1<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Zero<T>()), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Inf<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Minf<T>()), nt2::Zero<T>(), 0);

  nt2::table<T> a = _(T(-5), T(1), T(5));
  NT2_DISPLAY(a); 
  NT2_DISPLAY(exppdf(a)); 
} // end of test for floating_
 
NT2_TEST_CASE_TPL ( exppdf_2,  (float))//NT2_REAL_TYPES)
{
  
  using nt2::exppdf;
  using nt2::tag::exppdf_;
  using nt2::_; 
  

  // specific values tests
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Nan<T>(), nt2::One<T>()), nt2::Nan<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Zero<T>(), nt2::One<T>() ), nt2::One<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::One<T>(), nt2::One<T>()),   nt2::Invexp_1<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Inf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);
  NT2_TEST_ULP_EQUAL(exppdf(nt2::Minf<T>(), nt2::One<T>()), nt2::Zero<T>(), 0);

   nt2::table<T> a = _(T(-5), T(1), T(5));
   NT2_DISPLAY(a);
   NT2_DISPLAY(exppdf(a)); 
   NT2_DISPLAY(exppdf(a, nt2::One<T>()));
   NT2_DISPLAY(exppdf(nt2::One<T>(), a+T(10)));
   a = nt2::reshape(_(T(1), T(16)), 4, 4);
   NT2_DISPLAY(a); 
   nt2::table<T> z = exppdf(a, a+T(10)); 
   NT2_DISPLAY(z); 

   a = _(T(-5), T(1), T(5));
   nt2::table<T> b = _(T(1), T(1), T(11));
   NT2_DISPLAY(b); 

   NT2_DISPLAY(exppdf(a, b));
//    NT2_DISPLAY(b(_, 1));    
//    NT2_DISPLAY(exppdf(a, b(_, 1)));
//    NT2_DISPLAY( b(1, _)); 
//    NT2_DISPLAY(exppdf(a, b(1, _)));
} // end of test for floating_
 
