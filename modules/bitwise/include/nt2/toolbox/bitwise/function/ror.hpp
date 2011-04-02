//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_ROR_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_ROR_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/bitwise/include.hpp>

namespace nt2 { namespace tag
  {         
    struct ror_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::ror_, ror, 2)
}
 
#include <nt2/toolbox/bitwise/function/scalar/ror.hpp>
#include NT2_BITWISE_INCLUDE(ror.hpp) 

 
#endif

// modified by jt the 25/12/2010