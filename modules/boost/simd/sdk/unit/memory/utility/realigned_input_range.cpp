//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/realigned_input_range.hpp>
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
  using boost::simd::realigned_input_range;
  using boost::simd::pack;
  using boost::simd::allocator;

  // Take soemthign aligned and chirurgically unalign it
  std::vector<T, allocator<T> > data(pack<T>::static_size*4);
  typedef boost::iterator_range<typename std::vector<T, allocator<T> >::iterator> r_t;

  {
    NT2_TEST_EQUAL( std::distance ( boost::begin(realigned_input_range(data))
                                  , boost::end  (realigned_input_range(data))
                                  )
                  , 4
                  );
  }

  {
    r_t r = boost::make_iterator_range( data.begin() + 1, data.end() );

    NT2_TEST_EQUAL( std::distance ( boost::begin(realigned_input_range(r))
                                  , boost::end  (realigned_input_range(r))
                                  )
                  , 3
                  );
  }

  {
    r_t r = boost::make_iterator_range( data.begin(), data.end() -1 );

    NT2_TEST_EQUAL( std::distance ( boost::begin(realigned_input_range(r))
                                  , boost::end  (realigned_input_range(r))
                                  )
                  , 3
                  );
  }

  {
    r_t r = boost::make_iterator_range( data.begin() + 1, data.end() -1 );

    NT2_TEST_EQUAL( std::distance ( boost::begin(realigned_input_range(r))
                                  , boost::end  (realigned_input_range(r))
                                  )
                  , 2
                  );
  }
}

NT2_TEST_CASE_TPL(iteration, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::realigned_input_range;
  using boost::simd::pack;
  using boost::simd::dynarray;
  using boost::simd::allocator;
  using boost::simd::splat;
  using boost::begin;
  using boost::end;

  dynarray< pack<T> > dst(3);
  dynarray< pack<T> > ref(3);
  std::vector<T, allocator<T> >  data(pack<T>::static_size*4-1);

  for(std::size_t i=0;i<data.size();i++)
    data[i] = i/pack<T>::static_size+1;

  for(std::size_t i=0;i<ref.size();i++)
    ref[i] = splat< pack<T> >(i+1);

  mycopy( realigned_input_range(data), dst.begin());

  NT2_TEST_EQUAL( ref, dst );
}
