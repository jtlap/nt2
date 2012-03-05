/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container alignment"

#include <nt2/table.hpp>
#include <nt2/include/functions/toint.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>

// TODO: test the non-contiguous case

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

#ifndef BOOST_SIMD_NO_SIMD
  // Store unaligned data in aligned table
  table<T, settings(aligned_, shared_, no_padding_)> fake_aligned_table(of_size(32,32), share(q, q + 32 * 32));
  NT2_TEST_THROW( fake_aligned_table = aligned_table1, nt2::assert_exception );
#endif

  table<T, settings(aligned_, shared_, no_padding_)> aligned_table2(of_size(32,32), share(p, p + 32 * 32));
  table<T, settings(unaligned_, shared_, no_padding_)> unaligned_table2(of_size(32,32), share(q, q + 32 * 32));

  unaligned_table2 = aligned_table2;
  for (int i = 1; i < 32; i++)
    for (int j = 1; j < 32; j++)
      NT2_TEST_EQUAL( T(aligned_table2(i+1,j)),  T(unaligned_table2(i,j)) );

  table<T, settings(unaligned_, shared_, no_padding_)> fake_unaligned_table(of_size(32,32), share(p, p + 32 * 32));
  fake_unaligned_table = aligned_table2;

  a.deallocate(p,32*32+1);
}
