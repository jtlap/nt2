//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/arithmetic/include/functions/fms.hpp>
#include <boost/simd/include/functions/simd/enumerate.hpp>
#include <boost/simd/include/functions/simd/multiplies.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

NT2_TEST_CASE_TPL( fms,  BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::fms;
  using boost::simd::tag::fms_;
  using boost::simd::enumerate;
  using boost::simd::native;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;

  NT2_TEST_TYPE_IS( typename boost::dispatch::meta::call<fms_(vT,vT,vT)>::type
                  , vT
                  );

  vT a = enumerate<vT>(0,10);
  vT b = enumerate<vT>(0,2);
  vT c = enumerate<vT>(0,3);

  NT2_TEST_EQUAL(fms(a,b,c) , a*b-c );
}
