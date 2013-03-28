//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::algorithm"

#include <boost/simd/sdk/simd/algorithm.hpp>
#include <boost/simd/include/functions/plus.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <vector>
#include <algorithm>
#include <numeric>

#ifdef BOOST_MSVC
#pragma warning(disable: 4996) // std::transform on pointers may be unsafe
#endif

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
    return t0 + 1;
  }
};

namespace std
{
  template<class T, class Alloc>
  ostream& operator<<(ostream& os, vector<T, Alloc> const& v)
  {
    os << "\n";
    for(typename vector<T, Alloc>::const_iterator it = v.begin(); it != v.end(); ++it)
      os << *it << "  ";
    os << "\n";

    return os;
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with unary operation
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( transform_unary, BOOST_SIMD_SIMD_TYPES )
{
  std::vector<T> data_in(113);
  for(size_t i=0; i<113; ++i)
    data_in[i] = T(i);

  std::vector<T> data_out1(113);
  boost::simd::transform(&*data_in.begin(), &*data_in.end(), &*data_out1.begin(), plus_one());

  std::vector<T> data_out2(113);
  std::transform(&*data_in.begin(), &*data_in.end(), &*data_out2.begin(), plus_one());

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
  boost::simd::transform(&*data_in1.begin(), &*data_in1.end(), &*data_in2.begin(), &*data_out1.begin(), plus());

  std::vector<T> data_out2(113);
  std::transform(&*data_in1.begin(), &*data_in1.end(), &*data_in2.begin(), &*data_out2.begin(), plus());

  NT2_TEST_EQUAL(data_out1, data_out2);
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::accumulate
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL( accumulate, BOOST_SIMD_SIMD_TYPES )
{
  std::size_t n = 113;

  std::vector<T> data_in(n);
  for(size_t i=0; i<n; ++i)
    data_in[i] = T(i);

  T res1 = boost::simd::accumulate(&*data_in.begin(), &*data_in.end(), T(0), plus());
  T res2 = std::accumulate(&*data_in.begin(), &*data_in.end(), T(0), plus());

  NT2_TEST_EQUAL(res1, res2);
  NT2_TEST_EQUAL(res1, T((n-1)*n/2));
}
