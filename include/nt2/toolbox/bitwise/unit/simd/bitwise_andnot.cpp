//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 bitwise toolbox - bitwise_andnot/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// Test behavior of bitwise components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created  by $author$ the $date$
/// modified by $author$ the $date$
#include <nt2/sdk/memory/is_aligned.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/toolbox/bitwise/include/bitwise_andnot.hpp>
// specific includes for arity 2 tests
#include <nt2/toolbox/exponential/include/constants.hpp>
#include <nt2/toolbox/boost_math/include/bitwise_andnot.hpp>

NT2_TEST_CASE_TPL ( bitwise_andnot_real_convert__2,  NT2_REAL_CONVERTIBLE_TYPES)
{
  using nt2::bitwise_andnot;
  using nt2::tag::bitwise_andnot_;
  using nt2::load; 
  using nt2::simd::native;
  using nt2::meta::cardinal_of;
  typedef typename nt2::meta::upgrade<T>::type u_t;
  typedef typename nt2::meta::as_real<T>::type r_t;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>               n_t;
  typedef native<r_t,ext_t>            rn_t;
  typedef n_t                            vT;
  typedef typename nt2::meta::call<bitwise_andnot_(vT,vT)>::type call_type;

  // return type conformity test 
  NT2_TEST( (boost::is_same< call_type, rn_t >::value) );

} // end of test for real_convert_