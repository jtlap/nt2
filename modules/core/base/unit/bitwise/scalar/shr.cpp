//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - shr/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of bitwise components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 18/02/2011
///
#include <nt2/bitwise/include/functions/shr.hpp>
#include <nt2/include/functions/twopower.hpp>

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

#include <nt2/constant/constant.hpp>


NT2_TEST_CASE_TPL ( shr_unsigned_int__2_0,  NT2_UNSIGNED_TYPES)
{

  using nt2::shr;
  using nt2::tag::shr_;
  typedef T r_type;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<shr_(T,iT)>::type r_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;



  // specific values tests
  NT2_TEST_EQUAL(shr(T(2),1), nt2::One<T>());
  NT2_TEST_EQUAL(shr(nt2::Mone<T>(),(sizeof(r_type)*8-1)), nt2::One<r_t>());
  NT2_TEST_EQUAL(shr(nt2::Mone<T>(),(sizeof(r_type)*8-2)), nt2::Three<r_t>());
  NT2_TEST_EQUAL(shr(nt2::One<T>(),1), nt2::Zero<r_t>());
  NT2_TEST_EQUAL(shr(nt2::Zero<T>(),1), nt2::Zero<r_t>());
} // end of test for unsigned_int_
