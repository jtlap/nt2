//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 ieee toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/ieee/include/modf.hpp>
#include <nt2/include/functions/frac.hpp>
#include <nt2/include/functions/trunc.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/fusion/tuple.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


NT2_TEST_CASE_TPL ( modf,  (double)(float)
                  )
{
  using nt2::modf;
  using nt2::functors::modf_;
  typedef typename boost::result_of<nt2::meta::floating(T)>::type etype;
  typedef boost::fusion::tuple<etype, etype>                   type_t;
 
  NT2_TEST( (boost::is_same < typename nt2::meta::call<modf_(T)>::type
	     , type_t
              >::value)
           );

  T d[] = {1.25  , -1.35,  2};
  for(int i = 0;  i < 3;  i++){
    type_t r = modf(d[i]);
    NT2_TEST_EQUAL(  boost::fusion::get<1>(r), nt2::frac(d[i]));
    NT2_TEST_EQUAL(  boost::fusion::get<0>(r), nt2::trunc(d[i])); 
  }
}

