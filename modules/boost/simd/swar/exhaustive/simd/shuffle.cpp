//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/test/relation.hpp>
#include "roll_test.hpp"

NT2_TEST_CASE_TPL( shuffle_index4_1arg, (float)(int))
{
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,4>::type    vT;

  vT origin1;
  for(std::size_t i=0; i < vT::static_size;++i)
  {
    origin1[i] = T(65+i);
  }
  roll_unary_test_4<vT,-1,-1,-1,-1>::call(origin1);
}

NT2_TEST_CASE_TPL( shuffle_index4_2arg, (float)(int))
{
  using boost::simd::native;
  using boost::simd::meta::vector_of;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef typename vector_of<T,4>::type    vT;

  vT origin1, origin2;
  for(std::size_t i=0; i < vT::static_size;++i)
  {
    origin1[i] = T(65+i);
    origin2[i] = T(i);
  }

  roll_binary_test_4<vT,-1,-1,-1,-1>::call(origin1,origin2);
}
