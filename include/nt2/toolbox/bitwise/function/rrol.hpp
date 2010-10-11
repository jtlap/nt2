//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_RROL_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_RROL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/bitwise/include.hpp>

namespace nt2 { namespace functors
  {	       
    struct rrol_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(functors::rrol_, rrol, 2)
}
 
#include <nt2/toolbox/bitwise/function/scalar/rrol.hpp>
#include NT2_BITWISE_INCLUDE(rrol.hpp) 

 
#endif
