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
#include <nt2/toolbox/polynomials/include/polevl.hpp>
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/exp.hpp>
#include <boost/array.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( polevl, (double) 
                (float) (int32_t) (int64_t)
                )
{
  using nt2::polevl; 
  using nt2::tag::polevl_;
   NT2_TEST( (boost::is_same < typename nt2::meta::call<polevl_(T,boost::array<T,3>)>::type
            , typename boost::result_of<nt2::meta::floating(T)>::type
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t;
static const boost::array<T, 3 > A = {{1,2,3}}; 
   NT2_TEST_EQUAL(  nt2::polevl( T(0), A), T(3)  );
   NT2_TEST_EQUAL(  nt2::polevl( T(1), A), T(6)  );
   NT2_TEST_EQUAL(  nt2::polevl( T(2), A), T(11) );
   NT2_TEST_EQUAL(  nt2::polevl( T(8), A), T(83) ); 

}
