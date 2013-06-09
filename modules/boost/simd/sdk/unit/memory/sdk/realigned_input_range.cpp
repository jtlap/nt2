/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <boost/simd/memory/realigned_input_range.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/range/algorithm/copy.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <vector>

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
  using boost::simd::allocator;
  using boost::simd::splat;
  using boost::begin;
  using boost::end;

  std::vector< pack<T>, allocator<T> > dst(3);
  std::vector< pack<T>, allocator<T> > ref(3);
  std::vector<T, allocator<T> >  data(pack<T>::static_size*4-1);

  for(std::size_t i=0;i<data.size();i++)
    data[i] = i/pack<T>::static_size+1;

  for(std::size_t i=0;i<ref.size();i++)
    ref[i] = splat< pack<T> >(i+1);

  boost::copy( realigned_input_range(data), dst.begin());

  NT2_TEST_EQUAL( ref, dst );
}
