//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fdlibm toolbox - __ieee754_lgamma - unit/scalar Mode"
#include <nt2/include/functions/acos.hpp> 
#include <nt2/toolbox/fdlibm/include/__ieee754_lgamma.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>

//////////////////////////////////////////////////////////////////////////////
//Test behavior of fdlibm component __ieee754_lgamma using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( __ieee754_lgamma,  (double)(float) )
{
  using nt2::fdlibm::__ieee754_lgamma;
  using nt2::fdlibm::tag::__ieee754_lgamma_;

  NT2_TEST( (boost::is_same<typename nt2::meta::call<nt2::fdlibm::tag::__ieee754_lgamma_(T)>::type,
                           T
                           >::value)
          );
}