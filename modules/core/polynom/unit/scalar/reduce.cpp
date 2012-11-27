//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynom toolbox - reduce/scalar Mode" 

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of polynom components in scalar mode 
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 06/03/2011
/// 
#include <nt2/include/functions/reduce.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/isequal.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp> 
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/table.hpp>

#include <boost/array.hpp>


NT2_TEST_CASE_TPL ( reduce_real__1_0,  NT2_REAL_TYPES)
{ 
  
  using nt2::reduce;
  using nt2::tag::reduce_;
  nt2::table<T> a =  nt2::_(T(1), T(4));
  nt2::table<T> b =  nt2::_(T(0), T(0), T(3));
  nt2::table<T> c(nt2::of_size(1, 0));
  NT2_DISPLAY(a);
  NT2_DISPLAY(reduce(a)); 
  NT2_DISPLAY(b); 
  NT2_DISPLAY(reduce(b));
  NT2_DISPLAY(reduce(a, nt2::_));
  NT2_DISPLAY(reduce(a,nt2::Eps<T>())); 
  NT2_TEST(nt2::isequal(a, reduce(a)));
  NT2_TEST(nt2::isequal(a, reduce(a, nt2::Eps<T>()))); 
  NT2_TEST(nt2::isequal(a, reduce(a, nt2::_))); 
  NT2_TEST(nt2::isequal(c, reduce(b)));

} // end of test for floating_
  

