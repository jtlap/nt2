//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 cephes toolbox - ceil/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/cephes/include/ceil.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of cephes components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////

NT2_TEST_CASE_TPL ( real_ceil,  (double)(float)
                  )
{
  using nt2::cephes::ceil;
  using nt2::cephes::tag::ceil_;

 NT2_TEST( (boost::is_same < typename nt2::meta::call<ceil_(T)>::type
             ,T
             >::value)
          );
 NT2_TEST_EQUAL(  ceil( T(42.1) ), T(43) );
 NT2_TEST_EQUAL(  ceil( T(-42.1) ), T(-42) );

}

