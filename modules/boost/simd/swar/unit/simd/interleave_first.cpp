//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/include/functions/interleave_first.hpp>
#include <boost/simd/sdk/simd/native.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(interleave_first, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  typedef BOOST_SIMD_DEFAULT_EXTENSION      ext_t;
  typedef native<T,ext_t>                      vT;

  vT a,b,c;

  for(std::size_t i=1; i<=vT::static_size; ++i)
  {
    a[i-1]=T(i);
    b[i-1]=T(i*10);
  }

  c = boost::simd::interleave_first(a,b);

  std::size_t index = 0;
  for(std::size_t i=0; i<vT::static_size; ++i)
  {
    NT2_TEST_EQUAL(c[i],(i%2==0)?a[index]:b[index]);
    if(i%2!=0) index++;
  }
}
