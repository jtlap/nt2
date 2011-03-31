//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_PUT_FIRST_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_PUT_FIRST_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/swar/include.hpp>
#include <nt2/sdk/simd/native_cast.hpp>

namespace nt2 { namespace tag
  {         
    struct put_first_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::put_first_, put_first, 2)
}
 
#include <nt2/toolbox/swar/function/scalar/put_first.hpp>
#include NT2_SWAR_INCLUDE(put_first.hpp) 

 
#endif

// modified by jt the 25/12/2010
