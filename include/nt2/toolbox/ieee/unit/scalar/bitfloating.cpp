//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - unit/scalar Mode"

#include <nt2/toolbox/ieee/include/bitfloating.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of ieee components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/arg.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/as_real.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( bitfloating,  (nt2::int32_t)(nt2::uint32_t)  
                          (nt2::int64_t)(nt2::uint64_t)         
                  )
{
  using nt2::bitfloating;
  using nt2::functors::bitfloating_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<bitfloating_(T)>::type
	     , typename nt2::meta::as_real<T>::type
              >::value)
           );
  NT2_TEST_EQUAL(  bitfloating( T(0) ), T(0) );


}
