//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/trigonometric/include/functions/rem_pio2.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( rem_pio2_real__1_0,  NT2_REAL_TYPES)
{

  using nt2::rem_pio2;
  using nt2::tag::rem_pio2_;
  typedef typename nt2::meta::call<rem_pio2_(T)>::type r_t;
  typedef typename nt2::meta::call<rem_pio2_(T)>::type wished_r_t;


  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );

} // end of test for floating_
