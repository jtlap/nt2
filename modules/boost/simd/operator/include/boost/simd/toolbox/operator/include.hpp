//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_INCLUDE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_INCLUDE_HPP_INCLUDED
#include <boost/simd/sdk/simd/preprocessor/include.hpp>

#define BOOST_SIMD_OPERATOR_BASE() boost/simd/toolbox/operator/functions/scalar/
#define BOOST_SIMD_OPERATOR_RELATIVE() boost/simd/toolbox/operator/functions/

#define BOOST_SIMD_OPERATOR_INCLUDE(F) BOOST_SIMD_RELATIVE_INCLUDE(BOOST_SIMD_OPERATOR_RELATIVE, F)

#endif
