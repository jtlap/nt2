//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/ieee/include/functions/exponentbits.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/splat.hpp>

#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL ( exponentbits_real__1_0,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::exponentbits;
  using boost::simd::tag::exponentbits_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                 vT;

  for(int i=1; i < 10; i*= 2)
  {
    NT2_TEST_EQUAL(exponentbits(boost::simd::splat<vT>(i))[0],
                   exponentbits(T(i)));
  }
}
