//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 crlibm toolbox - unit/scalar Mode"

#include <nt2/sdk/functor/meta/call.hpp> 
#include <boost/type_traits/is_same.hpp>
#include <nt2/toolbox/crlibm/include/tanpi_rd.hpp> 
#include <nt2/sdk/unit/tests.hpp> 
#include <nt2/sdk/unit/module.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/include/functions/ulpdist.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of arithmetic components using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL ( tanpi_rd, (double) 
                (float) 
                )
{
  using nt2::crlibm::tanpi_rd; 
  using nt2::crlibm::tag::tanpi_rd_;
  const int N = 2; 
   NT2_TEST( (boost::is_same < typename nt2::meta::call<tanpi_rd_(T)>::type
            , T
            >::value)
           );
   typedef typename boost::result_of<nt2::meta::floating(T)>::type r_t; 
   NT2_TEST_EQUAL(  nt2::crlibm::tanpi_rd( T(0) )  , 0 );
   NT2_TEST_LESSER(  nt2::ulpdist(nt2::crlibm::tanpi_rd( T(1)) , T(0)),  N); 
   NT2_TEST_LESSER(  nt2::ulpdist(nt2::crlibm::tanpi_rd( T(0.25)  ) , T(1)),  N); 
}
