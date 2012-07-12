//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::transform"

#include <boost/simd/sdk/simd/iterator.hpp>
#include <boost/simd/sdk/simd/transform.hpp>
#include <boost/simd/sdk/simd/meta/unroll.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>

template<class Type>
struct op_
{
  op_(){}
  Type operator()(Type const& data){ return data; }
};

template<class Type>
struct sum_
{
  sum_(){}
  Type operator()(Type const& data1, Type const& data2)
  {
    Type res;
    res = data1 + data2;
    return res;
  }
};

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with unary operation and unroll<0>
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(transform_unary_correctly_sized, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::input_iterator<T>   it_;
  typedef typename boost::simd::output_iterator<T> out_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> >   data(32*card);
  std::vector<T, boost::simd::memory::allocator<T> > result(32*card);
  it_ dbegin  = boost::simd::input_begin(&data[0]);
  it_ dend    = boost::simd::input_end(&data[0]+32*card);
  out_ rbegin = boost::simd::output_begin(&result[0]);

  for(size_t i=0; i<32*card; ++i) data[i] = T(i);

  boost::simd::transform(dbegin, dend, rbegin, op_<p_t>());

  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator i = result.begin();
  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator j = data.begin();

  for(i = result.begin(); i != result.end(); ++i, ++j)
  {
    NT2_TEST_EQUAL( *i, *j);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with unary operation and unroll<4>
// Vector sizes are multiples of the unrolling.
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(transform_unary_correctly_sized_unroll4, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::input_iterator<T>   it_;
  typedef typename boost::simd::output_iterator<T> out_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> >   data(32*card);
  std::vector<T, boost::simd::memory::allocator<T> > result(32*card);
  it_ dbegin  = boost::simd::input_begin(&data[0]);
  it_ dend    = boost::simd::input_end(&data[0]+32*card);
  out_ rbegin = boost::simd::output_begin(&result[0]);

  for(size_t i=0; i<32*card; ++i) data[i] = T(i);

  boost::simd::transform( dbegin, dend, rbegin, op_<p_t>()
                        , boost::simd::meta::unroll<4>());

  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator i = result.begin();
  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator j = data.begin();

  for(i = result.begin(); i != result.end(); ++i, ++j)
  {
    NT2_TEST_EQUAL( *i, *j);
  }
}

////////////////////////////////////////////////////////////////////////////////
// Test boost::simd::transform behavior with unary operation and unroll<4>
// Vector sizes lead to extra computation that needs to be done properly and
// not unrolled.
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(transform_unary_bad_sized_unroll4, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::input_iterator<T>   it_;
  typedef typename boost::simd::output_iterator<T> out_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> >   data(19*card);
  std::vector<T, boost::simd::memory::allocator<T> > result(19*card);
  it_ dbegin  = boost::simd::input_begin(&data[0]);
  it_ dend    = boost::simd::input_end(&data[0]+19*card);
  out_ rbegin = boost::simd::output_begin(&result[0]);

  for(size_t i=0; i<19*card; ++i) data[i] = T(i);

  boost::simd::transform( dbegin, dend, rbegin, op_<p_t>()
                        , boost::simd::meta::unroll<4>());

  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator i = result.begin();
  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator j = data.begin();

  for(i = result.begin(); i != result.end(); ++i, ++j)
  {
    NT2_TEST_EQUAL( *i, *j);
  }
}

NT2_TEST_CASE_TPL(transform_binary_bad_sized_unroll4, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::input_iterator<T>   it_;
  typedef typename boost::simd::output_iterator<T> out_;
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::memory::allocator<T> >   data(19*card);
  std::vector<T, boost::simd::memory::allocator<T> >   data_(19*card);
  std::vector<T, boost::simd::memory::allocator<T> > result(19*card);
  it_ dbegin  = boost::simd::input_begin(&data[0]);
  it_ dbegin_ = boost::simd::input_begin(&data_[0]);
  it_ dend    = boost::simd::input_end(&data[0]+19*card);
  out_ rbegin = boost::simd::output_begin(&result[0]);

  for(size_t i=0; i<19*card; ++i) { data[i] = T(i%card); data_[i] = T(i%card); }

  boost::simd::transform( dbegin, dend, dbegin_, rbegin, sum_<p_t>()
                        , boost::simd::meta::unroll<4>());

  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator i = result.begin();
  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator j = data.begin();
  typename std::vector<T, boost::simd::memory::allocator<T> >::iterator j_ = data_.begin();

  for(i = result.begin(); i != result.end(); ++i, ++j, ++j_)
  {
    NT2_TEST_EQUAL( *i, (*j+*j_));
  }
}


