/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_DSL_PROTO_EXTENDS_HPP
#define BOOST_SIMD_SDK_DSL_PROTO_EXTENDS_HPP

#include <boost/simd/sdk/details/preprocessor.hpp>
////////////////////////////////////////////////////////////////////////////////
// BOOST_PROTO_BASIC_EXTENDS working with template Domain
////////////////////////////////////////////////////////////////////////////////
#define BOOST_PROTO_BASIC_EXTENDS_TPL(Expr, Derived, Domain)                  \
BOOST_PROTO_BASIC_EXTENDS_( BOOST_SIMD_PP_STRIP(Expr)                                \
                          , BOOST_SIMD_PP_STRIP(Derived)                             \
                          , BOOST_SIMD_PP_STRIP(Domain)                              \
                          )                                                   \
typedef void                                            proto_is_aggregate_;  \
typedef typename BOOST_SIMD_PP_STRIP(Domain)::proto_generator  proto_generator;      \
/**/

#endif
