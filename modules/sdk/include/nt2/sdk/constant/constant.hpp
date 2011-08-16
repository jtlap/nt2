//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_CONSTANT_CONSTANT_HPP_INCLUDED
#define NT2_SDK_CONSTANT_CONSTANT_HPP_INCLUDED

#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

#define NT2_CONSTANT_IMPLEMENTATION(TAG,NAME)                          \
BOOST_SIMD_CONSTANT_IMPLEMENTATION(TAG,NAME)

#define NT2_CONSTANT_REGISTER(TAG,TYPE,INT,FLOAT,DOUBLE)               \
BOOST_SIMD_CONSTANT_REGISTER(TAG,TYPE,INT,FLOAT,DOUBLE)

#define NT2_MAKE_STD_CONSTANT(NAME,HEXDOUBLE,HEXFLOAT,INT)             \
namespace tag                                                          \
{                                                                      \
    NT2_CONSTANT_REGISTER(NAME,double,INT,HEXFLOAT,HEXDOUBLE)          \
}                                                                      \
NT2_CONSTANT_IMPLEMENTATION(tag::NAME, NAME)                           \
/**/

#endif
