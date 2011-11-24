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
#include <boost/fusion/include/at_c.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/cat.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <iostream>

#define MAKE_ARGS(z, n, text) BOOST_PP_CAT(text,(i+n))

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::iterator behavior
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(simd_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::iterator<T>::iterator it_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  static const std::size_t at_ = card - 1;
  BOOST_SIMD_ALIGNED_TYPE(T) data[3*card];

  it_ begin = boost::simd::begin(&data[0]);
  it_ end   = boost::simd::end(&data[0]+3*card);

  for(int c = 0; begin != end; ++begin, c++)
  {
    for(int i=0;i<card;++i)
     NT2_TEST_EQUAL( (*begin)[i], data[i + c*card]);
  }
}
