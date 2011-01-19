//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 reduction toolbox - prod scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/toolbox/reduction/include/prod.hpp>

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of nt2::all in scalar mode
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( prod, (double)(nt2::uint64_t)(nt2::int64_t) 
                          (float)(nt2::uint32_t)(nt2::int32_t)  
                          (nt2::uint16_t)(nt2::int16_t)         
                          (nt2::uint8_t)(nt2::int8_t)
                  )
{
  using nt2::prod;
  using nt2::tag::prod_;

  NT2_TEST( (boost::is_same < typename nt2::meta::call<prod_(T)>::type
                            , typename std::tr1::result_of<nt2::meta::arithmetic(T)>::type
                            >::value)
          );
          
  NT2_TEST_EQUAL(  prod(T(0)) , T(0)  );
  NT2_TEST_EQUAL(  prod(T(1)) , T(1)  );
  NT2_TEST_EQUAL(  prod(T(42)), T(42) );
}
