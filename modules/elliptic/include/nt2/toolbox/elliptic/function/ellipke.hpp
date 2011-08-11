//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_ELLIPKE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_ELLIPKE_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/elliptic/include.hpp>

namespace nt2 {
  namespace tag
  {
    struct ellipke_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::ellipke_, ellipke, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::ellipke_, ellipke, 2)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipke_, ellipke,(A0 const&)(A1&)(A2&),3)
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::ellipke_, ellipke,(A0 const&)(A1 const&)(A2&)(A3&),4)
}

#endif
