//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/interleave_even.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>

NT2_TEST_CASE_TPL(interleave_even, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                      vT;

  const std::size_t card = cardinal_of<vT>::value;
  vT a,b,c,ref;

  for(std::size_t i=0; i<card; ++i)
  {
    a[i]=T(i+1);
    b[i]=T((i+1)*10);
  }

  for(std::size_t i=0;i<card;i+= 2)
  {
    ref[i]   = a[i];
    ref[i+1] = b[i];
  }

  c = boost::simd::interleave_even(a,b);

  NT2_TEST_EQUAL(c,ref);
}
