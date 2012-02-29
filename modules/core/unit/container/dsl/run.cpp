/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container runner"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/of_size.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

// TODO: test the non-contiguous case

NT2_TEST_CASE( value_at )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0(of_size(4, 3));
  table<T> a1(of_size(4, 3));

  for(std::size_t j=1; j!=3+1; ++j)
    for(std::size_t i=1; i!=4+1; ++i)
      a0(i, j) = T(i+j);

  a1 = a0 + T(1);

  for(std::size_t j=1; j!=3+1; ++j)
    for(std::size_t i=1; i!=4+1; ++i)
      NT2_TEST_EQUAL( T(a1(i, j)), T(i+j+1) );

  table<T, nt2::_1D> a2(of_size(13));
  table<T, nt2::_1D> a3(of_size(13));
  for(std::size_t i=1; i!=13+1; ++i)
    a2(i) = T(i);

  a3 = a2 + T(1);

  for(std::size_t i=1; i!=13+1; ++i)
    NT2_TEST_EQUAL( T(a3(i)), T(i+1) );

/*
  table<T, nt2::_1D> xd = nt2::_(T(0),T(2),T(9));
  table<T, nt2::_1D> a2_(of_size(5));
  a2_ = a2(xd);
*/
}

NT2_TEST_CASE( scalar_size )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0 = T(42);
  NT2_TEST( a0.extent() == of_size(1) );
  NT2_TEST_EQUAL( T(a0(1)), T(42) );

  table<T> a1;
  NT2_TEST( a1.extent() == of_size(0) );

  a1 = T(42);
  NT2_TEST( a1.extent() == of_size(1) );
  NT2_TEST_EQUAL( T(a0(1)), T(42) );
}

NT2_TEST_CASE( element_wise )
{
  using nt2::table;
  using nt2::of_size;
  typedef double T;

  table<T> a0;
  table<boost::dispatch::meta::as_integer<T>::type> a1;
  a1 = nt2::toint(a0);
}

NT2_TEST_CASE_TPL( alignment_load_store, BOOST_SIMD_SIMD_TYPES )
{
  using nt2::table;
  using nt2::settings;
  using nt2::of_size;
  using nt2::aligned_;
  using nt2::unaligned_;
  using nt2::shared_;
  using nt2::no_padding_;
  using nt2::share;

  boost::simd::memory::allocator<T> a;

  T *p = a.allocate(32*32+1);
  for (int i = 0; i < 32 * 32; i++)
    p[i] = (T)i;
  T *q = p + 1;

  table<T, settings(aligned_, shared_, no_padding_)> aligned_table1(of_size(32,32), share(p, p + 32 * 32));
  table<T, settings(unaligned_, shared_, no_padding_)> unaligned_table1(of_size(32,32), share(q, q + 32 * 32));

  aligned_table1 = unaligned_table1;
  for (int i = 1; i < 32; i++)
    for (int j = 1; j < 32; j++)
      NT2_TEST( T(aligned_table1(i+1,j)) == T(unaligned_table1(i,j)) );

  // Store unaligned data in aligned table
  table<T, settings(aligned_, shared_, no_padding_)> fake_aligned_table(of_size(32,32), share(q, q + 32 * 32));
  NT2_TEST_THROW( fake_aligned_table = aligned_table1, nt2::assert_exception );

  table<T, settings(aligned_, shared_, no_padding_)> aligned_table2(of_size(32,32), share(p, p + 32 * 32));
  table<T, settings(unaligned_, shared_, no_padding_)> unaligned_table2(of_size(32,32), share(q, q + 32 * 32));

  unaligned_table2 = aligned_table2;
  for (int i = 1; i < 32; i++)
    for (int j = 1; j < 32; j++)
      NT2_TEST( T(aligned_table2(i+1,j)) == T(unaligned_table2(i,j)) );

  table<T, settings(unaligned_, shared_, no_padding_)> fake_unaligned_table(of_size(32,32), share(p, p + 32 * 32));
  fake_unaligned_table = aligned_table2;

  a.deallocate(p,32*32+1);
}
