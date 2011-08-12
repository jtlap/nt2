//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_LIBC_INCLUDE_HPP_INCLUDED
#define NT2_TOOLBOX_LIBC_INCLUDE_HPP_INCLUDED
#include <boost/dispatch/details/preprocessor.hpp>
#include <math.h>

#define NT2_LIBC_BASE() nt2/toolbox/libc/functions/scalar/
#define NT2_LIBC_RELATIVE() nt2/toolbox/libc/functions/

#define NT2_LIBC_INCLUDE(F) NT2_SIMD_RELATIVE_INCLUDE(NT2_LIBC_RELATIVE, F)

#endif
