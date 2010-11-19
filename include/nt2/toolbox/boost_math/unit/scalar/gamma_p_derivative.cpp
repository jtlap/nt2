//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 boost_math toolbox - gamma_p_derivative - unit/scalar Mode"

#include <nt2/toolbox/boost_math/include/gamma_p_derivative.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/type_traits/is_same.hpp>

//////////////////////////////////////////////////////////////////////////////
// Test behavior of boost_math component gamma_p_derivative using NT2_TEST_CASE
//////////////////////////////////////////////////////////////////////////////
//NT2_TEST_CASE_TPL ( boost_math,  (double)(nt2::uint64_t)(nt2::int64_t) 
//                          (float)(nt2::uint32_t)(nt2::int32_t)  
//                          (nt2::uint16_t)(nt2::int16_t)         
//                          (nt2::uint8_t)(nt2::int8_t)
//                          (bool)
//                  )
//{
//  using nt2::gamma_p_derivative;
//  using nt2::functors::gamma_p_derivative_;
//
//  NT2_TEST( (boost::is_same<typename nt2::meta::call<boost_math_(T, T)>::type,
//                            typename std::tr1::result_of<nt2::meta::floating<($self.const_T_type_list$)>::type
//                            >::value)
//          );
//}