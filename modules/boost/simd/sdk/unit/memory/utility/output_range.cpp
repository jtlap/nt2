//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/output_range.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/range/algorithm/generate.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#include <vector>

NT2_TEST_CASE_TPL(distance, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::output_range;
  using boost::simd::pack;

  std::vector<T> data(pack<T>::static_size*3);

  NT2_TEST_EQUAL( std::distance ( boost::begin(output_range(data))
                                , boost::end(output_range(data))
                                )
                , 3
                );

  std::vector<T> fixed_data(24);

  NT2_TEST_EQUAL( std::distance ( boost::begin(output_range<8>(fixed_data))
                                , boost::end  (output_range<8>(fixed_data))
                                )
                , 3
                );
}

NT2_TEST_CASE_TPL(size_check, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::output_range;
  using boost::simd::pack;
  using boost::begin;
  using boost::end;

  std::vector<T> data(pack<T>::static_size*3-1);
  NT2_TEST_ASSERT( output_range(data) );

  std::vector<T> fixed_data(3*8-1);
  NT2_TEST_ASSERT( output_range<8>(data) );
}

template<class T> struct generate
{
  generate(T v) : value(v) {}
  boost::simd::pack<T> operator()() const
  {
    return boost::simd::splat< boost::simd::pack<T> >(value++);
  }

  private:
  mutable T value;
};


NT2_TEST_CASE_TPL(iteration, BOOST_SIMD_TYPES)
{
  using std::iterator_traits;
  using boost::simd::output_range;
  using boost::simd::output_iterator;
  using boost::simd::pack;

  std::size_t ps = pack<T>::static_size;
  std::vector<T>  ref (4*ps);
  std::vector<T>  data(4*ps);

//  typedef typename std::vector<T>::iterator it_t;
//  boost::iterator_range<output_iterator<it_t> > r = output_range(data);

  for(std::size_t i=0;i<data.size();i++)
    data[i] = T(0);

  for(std::size_t i=0;i<ref.size();i++)
    ref[i] = T(i/pack<T>::static_size+1);

  boost::generate( output_range(data), generate<T>(1));

  NT2_TEST_EQUAL( ref, data );
}
