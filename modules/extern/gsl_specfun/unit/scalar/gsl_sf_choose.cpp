//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 gsl_specfun toolbox - gsl_sf_choose - unit/scalar Mode"

//#include <nt2/toolbox/gsl_specfun/include/functions/gsl_sf_choose.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of gsl_specfun component gsl_sf_choose using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
//NT2_TEST_CASE_TPL ( gsl_specfun,  (double)(nt2::uint64_t)(nt2::int64_t)
//                          (float)(nt2::uint32_t)(nt2::int32_t)
//                          (nt2::uint16_t)(nt2::int16_t)
//                          (nt2::uint8_t)(nt2::int8_t)
//                          (bool)
//                  )
//{
//  using nt2::gsl_sf_choose;
//  using nt2::functors::gsl_sf_choose_;
//
//  NT2_TEST( (boost::is_same<typename nt2::meta::call<gsl_specfun_(T, T)>::type,
//                            typename nt2::meta::result_of<nt2::meta::floating<($self.const_T_type_list$)>::type
//                            >::value)
//          );
//}

