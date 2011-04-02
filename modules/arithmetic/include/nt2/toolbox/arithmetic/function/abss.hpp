//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_ABSS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_ABSS_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/arithmetic/include.hpp>

namespace nt2 {
  namespace tag
  {
    struct abss_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::abss_, abss, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::abss_, sturated_abs, 1)
}

#include <nt2/toolbox/arithmetic/function/scalar/abss.hpp>
#include NT2_ARITHMETIC_INCLUDE(abss.hpp) 

#endif
