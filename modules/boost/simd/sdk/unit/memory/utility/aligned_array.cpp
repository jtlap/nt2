//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/memory/aligned_array.hpp>

#include <boost/mpl/size_t.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

#ifdef BOOST_INTEL
#pragma warning(disable: 1366) // alignment of 1/2 doesn't do anything
#endif

NT2_TEST_CASE_TPL( aligned_array_alignment
                 , (boost::mpl::size_t<1>)(boost::mpl::size_t<2>)
                   (boost::mpl::size_t<4>)(boost::mpl::size_t<8>)
                   (boost::mpl::size_t<16>)(boost::mpl::size_t<32>)
                   (boost::mpl::size_t<64>)
                 )
{
  using boost::simd::aligned_array;
  aligned_array<float,18, T::value> tab;

  NT2_TEST( ((std::size_t)tab.data() % T::value) == 0 );
}

NT2_TEST_CASE( aligned_array_interface )
{
  using boost::simd::aligned_array;
  aligned_array<float,18> tab, tab_, tab__;

  for(int i=0; i<18; i++)
  {
    tab[i]  = float(i);
    tab_[i] = float(i*i);
  }

  for(int i=0; i<18; i++)
  {
    NT2_TEST_EQUAL( tab[i]   , float(i));
    NT2_TEST_EQUAL( tab.at(i), float(i));
  }

  tab.swap(tab_);
  tab__ = tab_;
  for(int i=0; i<18; i++)
  {
    NT2_TEST_EQUAL( tab[i]     , float(i*i));
    NT2_TEST_EQUAL( tab__.at(i), float(i));
  }

  NT2_TEST_EQUAL( tab.size(),     18u     );
  NT2_TEST_EQUAL( *(tab.begin()), tab[0]  );
  NT2_TEST_EQUAL( *(tab.end()-1), tab[17] );
  NT2_TEST_EQUAL( tab.empty(),    false   );
  NT2_TEST_EQUAL( tab.data(),     &tab[0] );

}

NT2_TEST_CASE( aligned_array_init )
{
  boost::simd::aligned_array<int, 3> tab = {{{1, 2, 3}}};
  for(int i=0; i<3; ++i)
    NT2_TEST_EQUAL( tab[i], i+1 );
}

NT2_TEST_CASE( const_aligned_array )
{
  const boost::simd::aligned_array<int, 3> tab = {{{1, 2, 3}}};
  const int * ptr = tab.data();

  NT2_TEST_EQUAL( ptr, &tab[0] );
}

NT2_TEST_CASE( empty_aligned_array )
{
  boost::simd::aligned_array<int, 0> tab;

  NT2_TEST(tab.empty());
  NT2_TEST_EQUAL(tab.size(), 0UL);
  NT2_TEST_EQUAL(tab.max_size(), 0UL);

  NT2_TEST(tab.begin()    == tab.end()   );
  NT2_TEST(tab.cbegin()   == tab.cend()  );
  NT2_TEST(tab.rbegin()   == tab.rend()  );
  NT2_TEST(tab.crbegin()  == tab.crend() );

  NT2_TEST_EQUAL(tab.c_array(), (int*)(0) );
  NT2_TEST_EQUAL(tab.data()   , (int*)(0) );

  NT2_TEST_ASSERT(tab[0]);
  NT2_TEST_ASSERT(tab.at(0));
  NT2_TEST_ASSERT(tab.front());
  NT2_TEST_ASSERT(tab.back());
}
