//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/allocator_adaptor.hpp>
#include <boost/simd/memory/is_aligned.hpp>

#include <vector>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>

NT2_TEST_CASE_TPL(vector, BOOST_SIMD_TYPES)
{
  using boost::simd::is_aligned;

  typedef std::allocator<T> base;
  typedef boost::simd::allocator_adaptor<base> alloc;
  std::vector<T, alloc > p(5);

  NT2_TEST( is_aligned( &p[0] ) );
  for(int i=0;i<5;++i) p[i] = T(10)*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(p[i],T(10)*i);
}

NT2_TEST_CASE_TPL(vector_n, BOOST_SIMD_TYPES)
{
  using boost::simd::is_aligned;

  typedef std::allocator<T> base;
  typedef boost::simd::allocator_adaptor<base,4> alloc;
  std::vector<T, alloc > p(5);

  NT2_TEST( is_aligned( &p[0], 4 ) );
  for(int i=0;i<5;++i) p[i] = T(10)*i;
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(p[i],T(10)*i);
}
