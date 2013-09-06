//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/sort.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/table.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <boost/simd/sdk/simd/io.hpp>

NT2_TEST_CASE_TPL ( sort, BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::native;
  using boost::simd::sort;
  using boost::dispatch::meta::as_;
  using boost::simd::tag::sort_;

  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef std::complex<T> cT;
  typedef native<cT,ext_t> vcT;
  typedef typename boost::dispatch::meta::call<sort_(vcT)>::type r_t;

  vcT a = boost::simd::enumerate<vcT>(cT(10,5));
  NT2_TEST_EQUAL(sort(a), a);
  a = boost::simd::enumerate<vcT>(cT(10,5), cT(-1, -1));
  int N = vcT::static_size-1;
  vcT b = boost::simd::enumerate<vcT>(cT(10-N, 5-N), cT(1, 1));
  NT2_TEST_EQUAL(sort(a), b);
 }
