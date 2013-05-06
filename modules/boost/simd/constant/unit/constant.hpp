//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef CONSTANT_HPP_INCLUDED
#define CONSTANT_HPP_INCLUDED

template<typename T> inline bool check_is_nan(T v) { return v!=v; }

#define NT2_CHECK_CONSTANT(CONSTANT,VALUE, TYPE)                               \
NT2_TEST_EXPR_TYPE(boost::simd::CONSTANT<TYPE>(), boost::mpl::_, TYPE);        \
NT2_TEST_EQUAL( boost::simd::CONSTANT<TYPE>(),boost::simd::splat<TYPE>(VALUE)) \
/**/

#endif
