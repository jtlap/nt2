//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/constants/true_false.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/tests/relation.hpp>
#include <nt2/sdk/unit/tests/type_expr.hpp>

#include "../constant.hpp"

NT2_TEST_CASE_TPL( true_false, BOOST_SIMD_TYPES )
{
  using boost::simd::logical;

  NT2_CHECK_CONSTANT(False, logical<T>(false) , logical<T> );
  NT2_CHECK_CONSTANT(True , logical<T>(true)  , logical<T> );
}
