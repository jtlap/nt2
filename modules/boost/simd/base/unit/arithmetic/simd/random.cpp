//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/random.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>

#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>


NT2_TEST_CASE_TPL ( random_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::random;
  using boost::simd::tag::random_;
  using boost::simd::native;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef typename boost::dispatch::meta::call<random_(vT,vT)>::type r_t;

 for(int i=0; i < 10; i++)
   {
     NT2_TEST_LESSER(random(boost::simd::splat<vT>(2), boost::simd::splat<vT>(3))[0], boost::simd::splat<T>(3));
     NT2_TEST_GREATER (random(boost::simd::splat<vT>(2), boost::simd::splat<vT>(3))[0], boost::simd::splat<T>(2));
   }

} // end of test for floating_
