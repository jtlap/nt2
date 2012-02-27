/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::iterator"

#include <boost/simd/sdk/simd/iterator.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::input_iterator behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(simd_input_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::input_iterator<T> it_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  static const std::size_t at_ = card - 1;
  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];

  for(int i=0; i<3*card; ++i) data[i] = i;

  it_ begin = boost::simd::input_begin(&data[0]);
  it_ end   = boost::simd::input_end(&data[0]+3*card);

  for(int c = 0; begin != end; ++begin, c++)
  {
    for(int i=0;i<card;++i)
     NT2_TEST_EQUAL( (*begin)[i], data[i + c*card]);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::input_iterator behavior with std::vector
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(simd_vector_input_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::input_iterator<T> it_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  static const std::size_t at_ = card - 1;
  std::vector<T, boost::simd::memory::allocator<T> > data(3*card);

  for(int i=0; i<3*card; ++i) data[i] = i;

  it_ begin = boost::simd::input_begin(data.begin());
  it_ end = boost::simd::input_end(data.end());

  for(int c = 0; begin != end; ++begin, c++)
  {
    for(int i=0;i<card;++i)
     NT2_TEST_EQUAL( (*begin)[i], data[i + c*card]);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::output_iterator behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(simd_output_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::output_iterator<T> oit_;
  typedef typename boost::simd::input_iterator<T>  iit_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  static const std::size_t at_ = card - 1;
  BOOST_SIMD_ALIGNED_TYPE(T) idata[3*card];
  BOOST_SIMD_ALIGNED_TYPE(T) odata[3*card];

  for(int i=0; i<3*card; ++i) idata[i] = i;

  oit_ obegin = boost::simd::output_begin(&odata[0]);
  oit_ oend   = boost::simd::output_end(&odata[0]+3*card);
  iit_ ibegin = boost::simd::input_begin(&idata[0]);
  iit_ iend   = boost::simd::input_end(&idata[0]+3*card);  
  
  for(; obegin != oend; ++obegin) *obegin = *ibegin++;

  iit_ rbegin = boost::simd::input_begin(&odata[0]);
  iit_ rend   = boost::simd::input_end(&odata[0]+3*card);  

  for(int c = 0; rbegin != rend; ++rbegin, c++)
  {
    for(int i=0;i<card;++i)
     NT2_TEST_EQUAL( (*rbegin)[i], idata[i + c*card]);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::output_iterator behavior with std::vector
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(simd_vector_output_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::output_iterator<T> oit_;
  typedef typename boost::simd::input_iterator<T>  iit_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  static const std::size_t at_ = card - 1;

  std::vector<T, boost::simd::memory::allocator<T> > idata(3*card);
  std::vector<T, boost::simd::memory::allocator<T> > odata(3*card);

  for(int i=0; i<3*card; ++i) idata[i] = i;

  oit_ obegin = boost::simd::output_begin(odata.begin());
  oit_ oend   = boost::simd::output_end(odata.end());
  iit_ ibegin = boost::simd::input_begin(idata.begin());
  iit_ iend   = boost::simd::input_end(idata.end());  
  
  for(; obegin != oend; ++obegin) *obegin = *ibegin++;

  iit_ rbegin = boost::simd::input_begin(&odata[0]);
  iit_ rend   = boost::simd::input_end(&odata[0]+3*card);  

  for(int c = 0; rbegin != rend; ++rbegin, c++)
  {
    for(int i=0;i<card;++i)
     NT2_TEST_EQUAL( (*rbegin)[i], idata[i + c*card]);
  }
}
