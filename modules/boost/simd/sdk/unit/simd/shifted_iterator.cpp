/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::shifted_iterator"

#include <boost/simd/sdk/simd/shifted_iterator.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::iterator behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(shifted_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef boost::simd::shifted_iterator<T,3> sit_;
  typedef boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  static const std::size_t at_ = card - 1;
  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];

  for(int i=0; i<3*card; ++i) data[i] = i;

  sit_ it(&data[0]);

  for(int i=0; i<2*card-3; ++i, ++it)
  {
    for(int j=0;j<card;++j)
    {
      NT2_TEST_EQUAL( ((*it)[0])[j], data[i + j]);
      NT2_TEST_EQUAL( ((*it)[1])[j], data[i+1+j]);
      NT2_TEST_EQUAL( ((*it)[2])[j], data[i+2+j]);
    }
  }

}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::iterator behavior with std::vector
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(shifted_vector_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::shifted_iterator<T,3> sit_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  static const std::size_t at_ = card - 1;
  std::vector<T, boost::simd::memory::allocator<T> > data(3*card);

  for(int i=0; i<3*card; ++i) data[i] = i;

  sit_ begin = boost::simd::begin<3>(data.begin());
  sit_ end = boost::simd::end<3>(data.end());

  for(int c = 0; begin != end; ++begin, c++)
  {
    for(int i=0;i<card;++i)
    {
      NT2_TEST_EQUAL( ((*begin)[0])[i], data[c + i]);
      NT2_TEST_EQUAL( ((*begin)[1])[i], data[c+1+i]);
      NT2_TEST_EQUAL( ((*begin)[2])[i], data[c+2+i]);
    }
  }
}
