//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.arithmetic toolbox - ceil/simd Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of boost.simd.arithmetic components in simd mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 28/11/2010
/// 
#include <nt2/toolbox/arithmetic/include/functions/ceil.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/splat.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>
#include <nt2/sdk/complex/dry.hpp>


NT2_TEST_CASE_TPL ( ceil_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
   using boost::simd::native;
  typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T>                         cT; 
  typedef native<T ,ext_t>                        vT;
  typedef native<cT ,ext_t>                      vcT;

  // specific values tests
//   NT2_TEST_EQUAL(ceil(nt2::splat<vcT>(cT(-1.1))), nt2::Mone<vcT>());
//   NT2_TEST_EQUAL(ceil(nt2::splat<vcT>(cT(-1.1))), nt2::Two<vcT>());  
//   NT2_TEST_EQUAL(ceil(nt2::Inf<vcT>()), nt2::Inf<vcT>());
//   NT2_TEST_EQUAL(ceil(nt2::Minf<vcT>()), nt2::Minf<vcT>());
//   NT2_TEST_EQUAL(ceil(nt2::Mone<vcT>()), nt2::Mone<vcT>());
//   NT2_TEST_EQUAL(ceil(nt2::Nan<vcT>()), nt2::Nan<vcT>());
//   NT2_TEST_EQUAL(ceil(nt2::One<vcT>()), nt2::One<vcT>());
//   NT2_TEST_EQUAL(ceil(nt2::Zero<vcT>()), nt2::Zero<vcT>());
} // end of test for floating_
