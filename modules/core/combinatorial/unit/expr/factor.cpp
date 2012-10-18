//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - factor/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
/// 
#include <nt2/toolbox/combinatorial/include/functions/factor.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/saturate.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/cast.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/tic.hpp>
#include <nt2/include/functions/toc.hpp>
#include <nt2/sdk/meta/type_id.hpp>

NT2_TEST_CASE_TPL ( factor_integer__1_0, NT2_INTEGRAL_TYPES)
{
  
  using nt2::factor;
  using nt2::tag::factor_;

  T p[] = {3, 5};
  nt2::table<T> myp = factor(T(15)); 
  // specific values tests
  
  for(size_t i=1; i <= nt2::length(myp); ++i)
    {
      NT2_TEST_EQUAL(p[i-1], myp(i)); 
    }
  myp = factor(T(15*3*2)); 
  // specific values tests
  T p1[] = {2, 3, 3, 5};
  NT2_DISPLAY(myp);
  
  for(size_t i=1; i <= nt2::length(myp); ++i)
    {
      std::cout << i << std::endl; 
      NT2_TEST_EQUAL(p1[i-1], myp(i)); 
    }
  
} 

NT2_TEST_CASE_TPL ( factor_integer__2_0, (int8_t))
{
  using nt2::factor;
  using nt2::tag::factor_;

 NT2_TEST_ASSERT(factor(T(15*3*2*2))); 
  
} 
