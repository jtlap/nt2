//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_HYPERBOLIC_INCLUDE_HPP_INCLUDED
#define NT2_TOOLBOX_HYPERBOLIC_INCLUDE_HPP_INCLUDED
#include <nt2/sdk/details/preprocessor.hpp>

#define NT2_HYPERBOLIC_BASE() nt2/toolbox/hyperbolic/function/scalar/
#define NT2_HYPERBOLIC_RELATIVE() nt2/toolbox/hyperbolic/function/

#if defined(NT2_SIMD_DETECTED)
#define NT2_HYPERBOLIC_INCLUDE(F) NT2_SIMD_RELATIVE_INCLUDE(NT2_HYPERBOLIC_RELATIVE, F)
#else
#define NT2_HYPERBOLIC_INCLUDE(F) NT2_PP_INCLUDE(NT2_HYPERBOLIC_BASE, F)
#endif

#endif
