//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 combinatorial toolbox - primes/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of combinatorial components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 07/03/2011
/// 
#include <nt2/toolbox/combinatorial/include/functions/primes.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/saturate.hpp>

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

NT2_TEST_CASE_TPL ( primes_integer__1_0,  (int32_t))//NT2_INTEGRAL_TYPES)
{
  
  using nt2::primes;
  using nt2::tag::primes_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<primes_(T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
 
  T p[6] = {2, 3, 5, 7, 11, 13};
  nt2::table<T> myp = primes(T(15)); 
  // specific values tests
  NT2_DISPLAY(myp); 
 for(size_t i=1; i <= 6; ++i)
   {
     NT2_TEST_EQUAL(p[i-1], myp(i)); 
   }
 nt2::tic(); 
 nt2::table<T> myp1 = primes(T(100000));
 nt2::toc(); 
 NT2_DISPLAY(primes(T(100)));

} 
