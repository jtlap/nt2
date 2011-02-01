//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/fuzzy/include.hpp>

namespace nt2 { namespace tag
  {         
    struct definitely_not_equal_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::definitely_not_equal_, definitely_not_equal, 3)
}
 
#include <nt2/toolbox/fuzzy/function/scalar/definitely_not_equal.hpp>
#include NT2_FUZZY_INCLUDE(definitely_not_equal.hpp) 

 
#endif

// modified by jt the 25/12/2010