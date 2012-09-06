//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_HPP_INCLUDED

/*!
 * \ingroup units
 * \defgroup utests Unit Test Checking
 * Define macro for building a Unit Test Case implementation
 */

#include <iomanip>
#include <vector>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/include/functions/random.hpp>
#include <boost/simd/sdk/memory/allocator.hpp>

#include <nt2/sdk/unit/tests/ulp.hpp>
#include <nt2/sdk/unit/tests/basic.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/exceptions.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#define NT2_CREATE_BUF(NAME, TYPE, SIZE, MIN, MAX)    \
  std::vector<TYPE,          \
          boost::simd::memory::allocator<TYPE> >    \
  NAME(SIZE);            \
  {\
    for(int k = 0; k < (int)SIZE; ++k){        \
    NAME[k] = nt2::random(MIN, MAX);        \
    }}                \
  /**/
#define NT2_CREATE_LOGICAL_BUF(NAME, TYPE, SIZE)\
  std::vector<TYPE,\
          boost::simd::memory::allocator<TYPE> >\
  NAME(SIZE);            \
  for(int k = 0; k < int(SIZE); ++k){          \
    NAME[k] = nt2::random(0, 1) ? nt2::True<TYPE>() : nt2::False<TYPE>(); \
  }                \
/**/
#define NT2_CREATE_BUFFER(NAME, TYPE, SIZE, MIN, MAX)  \
  std::vector<TYPE,        \
          boost::simd::memory::allocator<TYPE> >    \
          tab_##NAME(SIZE);    \
  {\
    for(int k = 0; k < (int)SIZE; ++k){      \
      NAME[k] = nt2::random(MIN, MAX);             \
   }}              \
/**/

#define NT2_CREATE_SCALAR_BUFFER(NAME, TYPE, SIZE, MIN, MAX)  \
  std::vector<TYPE,          \
          boost::simd::memory::allocator<TYPE> >    \
  tab_##NAME(SIZE);            \
  for(int k = 0; k < (int)SIZE; ++k){        \
    tab_##NAME[k] = nt2::random(MIN, MAX);      \
  }                \
/**/

#endif
