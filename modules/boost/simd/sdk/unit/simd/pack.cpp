//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/compare_equal.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/include/constants/one.hpp>

#include <boost/fusion/include/at.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <vector>

namespace foo
{
  template <int N> static int issue_495()
  {
    namespace bs = boost::simd;
    typedef boost::simd::pack<float, 4> tPack;

    tPack one (1.f);
    tPack two (2.f);

    one = one + two;
    one = one + 2.f;

    return 0;
  }
}

NT2_TEST_CASE(issue_495)
{
  foo::issue_495<4>();
  NT2_TEST_COMPLETE("Issue #495");
}

NT2_TEST_CASE(compare_equal)
{
  using namespace boost::simd;
  typedef pack<float, 2> f2;

  f2 f2_f (1);
  f2 f2_g (1);

  logical<float> ret1 = compare_equal(f2_f, f2_g);
  bool ret2 = compare_equal(f2_f, f2_g);
  NT2_TEST(ret1);
  NT2_TEST(ret2);
}

NT2_TEST_CASE(bitwise_cast_target)
{
  using namespace boost::simd;
  typedef pack<float, 2> ftype;
  typedef pack<int32_t, 2> itype;

  itype i(0x3f800000);
  NT2_TEST_EQUAL(bitwise_cast<ftype>(i), One<ftype>());
}

////////////////////////////////////////////////////////////////////////////////
// Test pack constructors
////////////////////////////////////////////////////////////////////////////////
NT2_TEST_CASE_TPL(constructor_from_values, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T,8> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;

  p_t p(T(1),T(2),T(3),T(4),T(5),T(6),T(7),T(8));

  for(size_t i=0;i<card;++i)
    NT2_TEST_EQUAL( p[i], T(1+i));
}

NT2_TEST_CASE_TPL(constructor_from_begin_iterator, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;

  BOOST_SIMD_ALIGNED_TYPE(T) data[card];
  for(size_t i=0; i<card; ++i) data[i] = T(i);

  p_t p(&data[0]);
  for(size_t i=0;i<card;++i)
    NT2_TEST_EQUAL( p[i], data[i]);
}

NT2_TEST_CASE_TPL(constructor_from_range, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::allocator<T> > data(card);

  for(size_t i=0; i<card; ++i) data[i] = T(i);

  p_t p(data.begin(),data.end());
  for(size_t i=0;i<card;++i)
    NT2_TEST_EQUAL( p[i], data[i]);
}

NT2_TEST_CASE_TPL(constructor_copy, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::allocator<T> > data(card);

  for(size_t i=0; i<card; ++i) data[i] = T(i);

  p_t p(data.begin(),data.end());
  p_t copy(p);

  for(size_t i=0;i<card;++i)
    NT2_TEST_EQUAL( copy[i], p[i]);
}

NT2_TEST_CASE_TPL(constructor_splat, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;

  p_t p(1);

  for(size_t i=0;i<card;++i)
    NT2_TEST_EQUAL( p[i], T(1));
}

NT2_TEST_CASE_TPL(range_interface, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::allocator<T> > data(card);

  for(size_t i=0; i<card; ++i) data[i] = T(i);

  p_t p(data.begin(),data.end());

  NT2_TEST_EQUAL( *(p.begin()), *(data.begin()));
  NT2_TEST_EQUAL( *(p.end()-1), *(data.end()-1));

}

NT2_TEST_CASE_TPL(pack_store, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::allocator<T> > data(card);
  std::vector<T, boost::simd::allocator<T> > stored(card);

  for(size_t i=0; i<card; ++i) data[i] = T(i);
  p_t p(data.begin(),data.end());
  boost::simd::aligned_store(p,&stored[0],0);

  NT2_TEST_EQUAL( *(stored.begin()), *(data.begin()));
  NT2_TEST_EQUAL( *(stored.end()-1), *(data.end()-1));

}

NT2_TEST_CASE_TPL(pack_load, BOOST_SIMD_SIMD_TYPES )
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::allocator<T> > data(card);

  for(size_t i=0; i<card; ++i) data[i] = T(i);
  p_t p;
  p = boost::simd::aligned_load<p_t>(&data[0],0);

  NT2_TEST_EQUAL( *(p.begin()), *(data.begin()));
  NT2_TEST_EQUAL( *(p.end()-1), *(data.end()-1));

}

template<class Seq>
struct iterate_test
{
  iterate_test(Seq const& s)
    : seq_(s) {}

  template<int I>
  void operator()() const
  {
    NT2_TEST_EQUAL( seq_[I], boost::fusion::at_c<I>(seq_));
  }

  Seq seq_;
};

NT2_TEST_CASE_TPL(pack_fusion, BOOST_SIMD_SIMD_TYPES)
{
  typedef typename boost::simd::pack<T> p_t;
  static const std::size_t card = boost::simd::meta::cardinal_of<p_t>::value;
  std::vector<T, boost::simd::allocator<T> > data(card);

  for(size_t i=0; i<card; ++i) data[i] = T(i);
  p_t p;
  p = boost::simd::aligned_load<p_t>(&data[0],0);

  boost::simd::meta::iterate<card>( iterate_test<p_t>(p));
}
