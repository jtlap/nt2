//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 fdlibm toolbox - __ieee754_remainder/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of fdlibm components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 03/03/2011
///
#include <nt2/toolbox/fdlibm/include/functions/__ieee754_remainder.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/remainder.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/idivround.hpp>

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
#include <nt2/include/constants/real.hpp>


NT2_TEST_CASE_TPL ( __ieee754_remainder_real__2_0,  NT2_REAL_TYPES)
{

  using nt2::fdlibm::__ieee754_remainder;
  using nt2::fdlibm::tag::__ieee754_remainder_;
  typedef typename nt2::meta::as_integer<T>::type iT;
  typedef typename nt2::meta::call<__ieee754_remainder_(T,T)>::type r_t;
  typedef typename nt2::meta::scalar_of<r_t>::type ssr_t;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef T wished_r_t;


  // return type conformity test
  NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
  std::cout << std::endl;
  double ulpd;
  ulpd=0.0;

} // end of test for floating_
