//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 polynomials toolbox - unit/scalar Mode"
#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/polynomials/include/legendre.hpp>
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/exp.hpp>
#include <boost/math/special_functions/legendre.hpp>


//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( legendre, (double) 
                (float)
                )
{

  using nt2::tag::legendre_;
  NT2_TEST( (boost::is_same < typename nt2::meta::call<legendre_(uint32_t, T)>::type
             , typename boost::result_of<nt2::meta::floating(T)>::type
             >::value)
            );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t;

   NT2_TEST_EQUAL(  nt2::legendre( 1,T(0    ) ) , boost::math::legendre_p( 1,T(0    )) );
   NT2_TEST_EQUAL(  nt2::legendre( 2,T(0.5  ) ) , boost::math::legendre_p( 2,T(0.5  )) );
   NT2_TEST_EQUAL(  nt2::legendre( 1,T(-0.5 ) ) , boost::math::legendre_p( 1,T(-0.5 )) );
   NT2_TEST_EQUAL(  nt2::legendre( 2,T(0.25 ) ) , boost::math::legendre_p( 2,T(0.25 )) );
   NT2_TEST_EQUAL(  nt2::legendre( 2,T(-0.25) ) , boost::math::legendre_p( 2,T(-0.25)) );  

}
