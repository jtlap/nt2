//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_INCLUDE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_INCLUDE_HPP_INCLUDED
#include <nt2/sdk/simd/preprocessor/include.hpp>

#define NT2_OPERATOR_BASE() nt2/toolbox/operator/function/scalar/
#define NT2_OPERATOR_RELATIVE() nt2/toolbox/operator/function/

#define NT2_OPERATOR_INCLUDE(F) NT2_SIMD_RELATIVE_INCLUDE(NT2_OPERATOR_RELATIVE, F)

#endif
