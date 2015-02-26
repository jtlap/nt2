//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2015   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2015   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(disable: 4996) // std::transform on pointers may be unsafe
#endif

#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/sdk/simd/algorithm.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/constants/one.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

struct plus
{
  template<class T>
  T operator()(T const& t0, T const& t1) const
  {
    return t0 + t1;
  }
};

struct plus_one
{
  template<class T>
  T operator()(T const& t0) const
  {
    using boost::simd::One;
    return t0 + One<T>();
  }
};

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with unary operation
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( transform_unary, BOOST_SIMD_SIMD_TYPES )
{
  std::vector<T> data_in(113);
  for(size_t i=0; i<113; ++i)
    data_in[i] = T(i);

  std::vector<T> data_out1(113);
  boost::simd::transform(&*data_in.begin(), &*data_in.begin()+data_in.size(), &*data_out1.begin(), plus_one());

  std::vector<T> data_out2(113);
  std::transform(&*data_in.begin(), &*data_in.begin()+data_in.size(), &*data_out2.begin(), plus_one());

  NT2_TEST_EQUAL(data_out1, data_out2);
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with binary operation
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( transform_binary, BOOST_SIMD_SIMD_TYPES )
{
  std::vector<T> data_in1(113);
  std::vector<T> data_in2(113);
  for(size_t i=0; i<113; ++i)
  {
    data_in1[i] = T(i);
    data_in2[i] = T(10 + i);
  }

  std::vector<T> data_out1(113);
  boost::simd::transform(&*data_in1.begin(), &*data_in1.begin()+data_in1.size(), &*data_in2.begin(), &*data_out1.begin(), plus());

  std::vector<T> data_out2(113);
  std::transform(&*data_in1.begin(), &*data_in1.begin()+data_in1.size(), &*data_in2.begin(), &*data_out2.begin(), plus());

  NT2_TEST_EQUAL(data_out1, data_out2);
}

template<typename T> inline void check_accumulate(T* b, T* e)
{
  T res1 = boost::simd::accumulate(b, e, T(0), plus());
  T res2 =         std::accumulate(b, e, T(0), plus());

  NT2_TEST_EQUAL(res1, res2);
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::accumulate
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( accumulate, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::native;
  using boost::simd::meta::cardinal_of;

  auto c = cardinal_of<native<T,BOOST_SIMD_DEFAULT_EXTENSION>>::value;
  auto n = 3*c;

  std::vector<T,boost::simd::allocator<T>> data(n);
  auto b = data.data();

  check_accumulate(b,b+n);
  check_accumulate(b+1,b+n);
  check_accumulate(b,b+n-1);
  check_accumulate(b+1,b+n-1);
}
