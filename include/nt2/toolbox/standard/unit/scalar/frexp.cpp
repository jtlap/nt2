//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 standard toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/standard/include/frexp.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


NT2_TEST_CASE_TPL ( frexp,  (double)(float)
                  )
{
  using nt2::standard::frexp;
  using nt2::standard::tag::frexp_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type mantissa;
  typedef typename nt2::meta::as_integer<T,signed>::type          exponent;
  typedef boost::fusion::vector<mantissa,exponent>                   type_t;
 
  NT2_TEST( (boost::is_same < typename nt2::meta::call<frexp_(T)>::type
           , type_t
              >::value)
           );

  T d[] = {1  , -1 };
  T m[] = {0.5, -0.5};
  T e[] = {1  , 1  };
  for(int i = 0;  i < 2;  i++){
    type_t r = frexp(d[i]);
    NT2_TEST_EQUAL(  boost::fusion::at_c<0>(r), m[i]);
    NT2_TEST_EQUAL(  boost::fusion::at_c<1>(r), e[i]); 
  }
}

