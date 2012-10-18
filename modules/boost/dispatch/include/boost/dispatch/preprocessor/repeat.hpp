//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_PREPROCESSOR_REPEAT_HPP_INCLUDED
#define BOOST_DISPATCH_PREPROCESSOR_REPEAT_HPP_INCLUDED

#define BOOST_DISPATCH_PP_REPEAT_POWER_OF_2(m, data)                           \
m( 1,  1, data)                                                                \
m( 2,  2, data)                                                                \
m( 4,  4, data)                                                                \
m( 8,  8, data)                                                                \
m(16, 16, data)                                                                \
m(32, 32, data)                                                                \
m(64, 64, data)                                                                \
/**/

#endif