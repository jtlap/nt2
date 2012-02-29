/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 0x01.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "boost::simd::pack"

#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>

////////////////////////////////////////////////////////////////////////////////
// Test pack constructors
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(constructor_from_begin_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;

  BOOST_SIMD_ALIGNED_TYPE(T) data[card];
  for(int i=0; i<card; ++i) data[i] = i;

  p_t p(&data[0]);
  for(int i=0;i<card;++i)
    NT2_TEST_EQUAL( p[i], data[i]);
}

NT2_TEST_CASE_TPL(constructor_from_range, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> > data(card);

  for(int i=0; i<card; ++i) data[i] = i;

  p_t p(data.begin(),data.end());
  for(int i=0;i<card;++i)
    NT2_TEST_EQUAL( p[i], data[i]);
}

NT2_TEST_CASE_TPL(constructor_copy, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> > data(card);

  for(int i=0; i<card; ++i) data[i] = i;

  p_t p(data.begin(),data.end());
  p_t copy(p);

  for(int i=0;i<card;++i)
    NT2_TEST_EQUAL( copy[i], p[i]);
}

NT2_TEST_CASE_TPL(constructor_splat, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;

  p_t p(1);

  for(int i=0;i<card;++i)
    NT2_TEST_EQUAL( p[i], T(1));
}

NT2_TEST_CASE_TPL(range_interface, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> > data(card);

  for(int i=0; i<card; ++i) data[i] = i;

  p_t p(data.begin(),data.end());

  NT2_TEST_EQUAL( *(p.begin()), *(data.begin()));
  NT2_TEST_EQUAL( *(p.end()-1), *(data.end()-1));

}

NT2_TEST_CASE_TPL(pack_store, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> > data(card);
  std::vector<T, boost::simd::memory::allocator<T> > stored(card);

  for(int i=0; i<card; ++i) data[i] = i;
  p_t p(data.begin(),data.end());
  boost::simd::store(p,&stored[0],0);

  NT2_TEST_EQUAL( *(stored.begin()), *(data.begin()));
  NT2_TEST_EQUAL( *(stored.end()-1), *(data.end()-1));

}

NT2_TEST_CASE_TPL(pack_load, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> > data(card);

  for(int i=0; i<card; ++i) data[i] = i;
  p_t p;
  p = boost::simd::load<p_t>(&data[0],0);

  NT2_TEST_EQUAL( *(p.begin()), *(data.begin()));
  NT2_TEST_EQUAL( *(p.end()-1), *(data.end()-1));

}
