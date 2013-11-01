//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <boost/simd/boolean/include/functions/mask2logical.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/inf.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/minf.hpp>
#include <boost/simd/include/constants/mone.hpp>
#include <boost/simd/include/constants/nan.hpp>
#include <boost/simd/include/constants/allbits.hpp>



NT2_TEST_CASE_TPL ( mask2logical_real,  BOOST_SIMD_SIMD_REAL_TYPES)
{
  using boost::simd::mask2logical;
  using boost::simd::tag::mask2logical_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< logical<T>, ext_t>             vlT;


  // specific values tests
  NT2_TEST_EQUAL(mask2logical(boost::simd::Zero<vT>()), boost::simd::False<vlT>());
  NT2_TEST_EQUAL(mask2logical(boost::simd::Nan<vT>()) , boost::simd::True<vlT>());
} // end of test for floating_

NT2_TEST_CASE_TPL ( mask2logical_signed_int,  BOOST_SIMD_SIMD_INTEGRAL_SIGNED_TYPES)
{

  using boost::simd::mask2logical;
  using boost::simd::tag::mask2logical_;
  using boost::simd::native;
  using boost::simd::logical;
  typedef BOOST_SIMD_DEFAULT_EXTENSION  ext_t;
  typedef native<T,ext_t>                  vT;
  typedef native< logical<T>, ext_t>             vlT;

  // specific values tests
  NT2_TEST_EQUAL(mask2logical(boost::simd::Zero<vT>()), boost::simd::False<vlT>());
  NT2_TEST_EQUAL(mask2logical(boost::simd::Mone<vT>()) , boost::simd::True<vlT>());
} // end of test for signed_int_
