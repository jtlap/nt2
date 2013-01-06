//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::range SIMD"

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/range.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/range/numeric.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/type_traits/is_same.hpp>
#include <vector>
#include <algorithm>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::input_range
////////////////////////////////////////////////////////////////////////////////

template<class It, class Val>
Val accumulate(It begin, It end, Val const& val_)
{
  Val val = val_;
  for(; begin != end; ++begin)
    val = (Val)(val + *begin);
  return val;
}

template<class Range, class Val>
Val accumulate(Range const& range, Val const& val)
{
  return ::accumulate(boost::begin(range), boost::end(range), val);
}

NT2_TEST_CASE_TPL(input_range_interface, BOOST_SIMD_SIMD_TYPES)
{
  std::vector<T,boost::simd::memory::allocator<T> > v(1024);
  std::vector<T,boost::simd::memory::allocator<T> > c(1024);
  for(std::size_t i=0; i<v.size(); ++i) v[i] = T(i);

  typedef boost::simd::pack<T> p_t;

  p_t x,z;
  T r;
  z = boost::simd::Zero<p_t>();
  x = ::accumulate(boost::simd::range(v),z);
  r = ::accumulate(x.begin(),x.end(),T(0.0));
  NT2_TEST_EQUAL(r,std::accumulate(v.begin(),v.end(),T(0.0)));
}
