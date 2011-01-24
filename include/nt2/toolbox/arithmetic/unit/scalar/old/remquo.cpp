//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 arithmetic toolbox - remquo/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/arithmetic/include/remquo.hpp>
#include <nt2/toolbox/arithmetic/include/remainder.hpp>
// #include <nt2/toolbox/arithmetic/include/idivfix.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
// #include <nt2/include/functions/ulpdist.hpp>
#include <boost/fusion/tuple.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////


NT2_TEST_CASE_TPL ( remquo,  (double)
                          (float)
                  )
{
  using nt2::remquo;
  using nt2::tag::remquo_;

  typedef typename boost::result_of<nt2::meta::floating(T, T)>::type rem;
  typedef typename nt2::meta::as_integer<T,signed>::type             quo;
  typedef boost::fusion::tuple<rem,quo>                           type_t;
  NT2_TEST( (boost::is_same < typename nt2::meta::call<remquo_(T, T)>::type
              , type_t
              >::value)
           );

  T n[] = {3  , 2,  11.4};
  T d[] = {1  , -1, 2.23};
 
  for(int i = 0;  i < 3;  i++){
    type_t r = remquo(n[i], d[i]);
    NT2_TEST_EQUAL(  boost::fusion::get<0>(r), nt2::remainder(n[i], d[i]));
    NT2_TEST_EQUAL(  boost::fusion::get<1>(r), nt2::idivfix(n[i], d[i]));
  }
}
          
