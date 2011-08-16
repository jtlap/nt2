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
#include <boost/simd/toolbox/constant/constants/macros.hpp>
#include <nt2/include/functor.hpp>

#define NT2_MAKE_STD_CONSTANT(NAME,HEXDOUBLE,HEXFLOAT,INT)             \
BOOST_SIMD_STD_CONSTANT_TAG(NAME)                                      \
BOOST_SIMD_STD_CONSTANT_DEF(NAME)                                      \
BOOST_SIMD_STD_CONSTANT_FUNCTOR((nt2), (ext), NAME, HEXDOUBLE, HEXFLOAT, INT) \
BOOST_SIMD_PROTOIZE_CONSTANT(NAME)                                     \
/**/

#endif
