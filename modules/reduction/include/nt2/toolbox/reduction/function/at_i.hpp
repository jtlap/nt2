//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_AT_I_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_AT_I_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/reduction/include.hpp>

namespace nt2 {
  namespace tag
  {
    struct at_i_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::at_i_, at_i, 2)
  NT2_FUNCTION_IMPLEMENTATION(tag::at_i_, at, 2)
}

#include <nt2/toolbox/reduction/function/scalar/at_i.hpp>
#include NT2_REDUCTION_INCLUDE(at_i.hpp) 

#endif
