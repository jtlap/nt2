//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 reduction toolbox - second scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/toolbox/reduction/include/second.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of nt2::second in scalar mode
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( second, (double)(nt2::uint64_t)(nt2::int64_t) 
                        (float)(nt2::uint32_t)(nt2::int32_t)  
                        (nt2::uint16_t)(nt2::int16_t)         
                        (nt2::uint8_t)(nt2::int8_t)
                        (bool)
                  )
{
  using nt2::second;
  using nt2::tag::second_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<second_(T)>::type
                            , T
                            >::value)
          );

  NT2_TEST_EQUAL(  second( T(42) ), T(42) );
}
