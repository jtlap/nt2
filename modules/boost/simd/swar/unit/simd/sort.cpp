//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/swar/include/functions/sort.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <iostream>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL ( sort, BOOST_SIMD_SIMD_TYPES)
{
  using boost::simd::native;
  using boost::simd::sort;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t> vT;

  vT ordered, reversed, mixed;
  for(std::size_t i=0; i!=vT::static_size; ++i)
  {
    ordered[i] = T(i);
    reversed[vT::static_size-1-i] = T(i);
    mixed[(i % 2) ? (vT::static_size-i) : i] = T(i);
  }

  NT2_TEST_EQUAL(sort(ordered), ordered);
  NT2_TEST_EQUAL(sort(reversed), ordered);

  std::cout << "mixed = " << mixed << std::endl;
  NT2_TEST_EQUAL(sort(mixed), ordered);
 }
