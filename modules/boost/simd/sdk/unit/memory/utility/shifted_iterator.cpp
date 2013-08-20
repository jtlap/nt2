//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/shifted_iterator.hpp>
#include <boost/simd/memory/output_iterator.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>

template<class T>
struct average
{
  template<class Region>
  boost::simd::pack<T> operator()(Region const& r)
  {
    return (r[0]+r[1]+r[2]);
  }
};

template<typename In, typename Out, typename F>
inline Out mytransform(In const& b, In const& e, Out const& o, F f)
{
  In  lb = b;
  Out lo = o;
  for(;lb!=e;) *lo++ = f(*lb++);
  return lo;
}

NT2_TEST_CASE_TPL(shifted_vector_iterator_scalar, BOOST_SIMD_SIMD_TYPES )
{
  using boost::simd::output_iterator;
  using boost::simd::output_begin;
  using boost::simd::shifted_iterator;
  using boost::simd::shifted_begin;
  using boost::simd::shifted_end;
  using boost::simd::allocator;
  using boost::simd::region_;
  using boost::simd::around;
  using boost::simd::pack;
  using boost::simd::meta::cardinal_of;

  typedef typename std::vector<T, allocator<T> >::iterator it_t;
  typedef shifted_iterator<it_t,region_<-1,1> > sit_;
  typedef pack<T> p_t;

  static const std::size_t card = cardinal_of<p_t>::value;
  std::vector<T,allocator<T> > data(card*6);
  std::vector<T,allocator<T> > ref(card*6);
  std::vector<T,allocator<T> > result(card*6);

  for(std::size_t i=0; i<data.size(); ++i)
  {
    data[i] = T(i+1-card);
  }

  for(std::size_t i=card; i<ref.size()-card; ++i) ref[i] = T((i+1-card)*3);

  sit_ sb = boost::simd::shifted_begin(data.begin(), around<-1,1>());
  sit_ se = boost::simd::shifted_end(data.end(), around<-1,1>());

  mytransform( sb, se, output_begin(result.begin())+1, average<T>() );

  NT2_TEST_EQUAL(result,ref);
}
