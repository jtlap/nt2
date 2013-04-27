//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "boost::simd::memory::allocate and related functions"

#include <boost/simd/memory/new.hpp>
#include <boost/simd/memory/is_aligned.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>

NT2_TEST_CASE_TPL(new_delete, BOOST_SIMD_TYPES)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  T* ptr = 0;
  NT2_TEST( is_aligned(ptr = new T) );
  delete ptr;

  NT2_TEST( is_aligned(ptr = new T[5]) );

  for(int i=0;i<5;++i) ptr[i] = T(10*i);
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],T(10*i));
  delete[] ptr;
}

NT2_TEST_CASE_TPL(new_delete_aligned, BOOST_SIMD_TYPES)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  T* ptr = 0;
  NT2_TEST( is_aligned(ptr = new(64) T, 64) );
  delete ptr;

  NT2_TEST( is_aligned(ptr = new(64) T[5], 64) );

  for(int i=0;i<5;++i) ptr[i] = T(10*i);
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],T(10*i));
  delete[] ptr;
}

NT2_TEST_CASE_TPL(new_delete_no_throw, BOOST_SIMD_TYPES)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  T* ptr = 0;
  NT2_TEST( is_aligned(ptr = new(std::nothrow) T) );
  delete ptr;

  NT2_TEST( is_aligned(ptr = new(std::nothrow) T[5]) );

  for(int i=0;i<5;++i) ptr[i] = T(10*i);
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],T(10*i));
  delete[] ptr;
}

NT2_TEST_CASE_TPL(new_delete_no_throw_aligned, BOOST_SIMD_TYPES)
{
  using boost::simd::memory::byte;
  using boost::simd::memory::allocate;
  using boost::simd::memory::deallocate;
  using boost::simd::is_aligned;

  T* ptr = 0;
  NT2_TEST( is_aligned(ptr = new(64,std::nothrow) T, 64) );
  delete ptr;

  NT2_TEST( is_aligned(ptr = new(64,std::nothrow) T[5], 64) );

  for(int i=0;i<5;++i) ptr[i] = T(10*i);
  for(int i=0;i<5;++i) NT2_TEST_EQUAL(ptr[i],T(10*i));
  delete[] ptr;
}
