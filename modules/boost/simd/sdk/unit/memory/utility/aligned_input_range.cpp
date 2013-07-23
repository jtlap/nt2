//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/aligned_input_range.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/memory/dynarray.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/range.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <vector>

template<typename Range, typename Out>
inline Out mycopy(Range const& r, Out dst)
{
  typedef typename std::iterator_traits<Out>::value_type T;
  typedef typename boost::range_iterator<Range>::type it_t;

  it_t begin = boost::begin(r);
  it_t end = boost::end(r);

  for(; begin != end; ++begin) *dst++ = T(*begin);

  return dst;
}


NT2_TEST_CASE_TPL(distance, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::aligned_input_range;
  using boost::simd::pack;
  using boost::simd::allocator;

  std::vector<T, allocator<T> > data(pack<T>::static_size*3);

  NT2_TEST_EQUAL( std::distance ( boost::begin(aligned_input_range(data))
                                , boost::end(aligned_input_range(data))
                                )
                , 3
                );
}

NT2_TEST_CASE_TPL(size_check, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::aligned_input_range;
  using boost::simd::pack;
  using boost::simd::allocator;
  using boost::begin;
  using boost::end;

  std::vector<T, allocator<T> > data(pack<T>::static_size*3-1);
  NT2_TEST_ASSERT( aligned_input_range(data) );
}

NT2_TEST_CASE_TPL(iteration, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::aligned_input_range;
  using boost::simd::allocator;
  using boost::simd::dynarray;
  using boost::simd::pack;
  using boost::simd::splat;
  using boost::begin;
  using boost::end;

  dynarray< pack<T> > dst(3);
  dynarray< pack<T> > ref(3);
  std::vector<T, allocator<T> > data(pack<T>::static_size*3);

  for(std::size_t i=0;i<data.size();i++)
    data[i] = i/pack<T>::static_size+1;

  for(std::size_t i=0;i<ref.size();i++)
    ref[i] = splat< pack<T> >(i+1);

  mycopy( aligned_input_range(data), dst.begin());

  NT2_TEST_EQUAL( ref, dst );
}
