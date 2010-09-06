/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_ARITHMETIC_INCLUDE_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_INCLUDE_HPP_INCLUDED

//#include <nt2/include/simd.hpp>
#include <nt2/sdk/details/preprocessor.hpp>

#define NT2_ARITHMETIC_BASE() nt2/toolbox/arithmetic/function/scalar/
#define NT2_ARITHMETIC_RELATIVE() nt2/toolbox/arithmetic/function/

#if defined(NT2_SIMD_DETECTED)
#define NT2_ARITHMETIC_INCLUDE(F) NT2_SIMD_RELATIVE_INCLUDE(NT2_ARITHMETIC_RELATIVE, F)
#else
#define NT2_ARITHMETIC_INCLUDE(F) NT2_PP_INCLUDE(NT2_ARITHMETIC_BASE, F)
#endif

#endif

// /////////////////////////////////////////////////////////////////////////////
// End of include.hpp
// /////////////////////////////////////////////////////////////////////////////
