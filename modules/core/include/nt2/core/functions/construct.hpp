//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_CONSTRUCT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_CONSTRUCT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2 
{ 
  namespace tag { struct construct_ : ext::unspecified_<construct_> {}; }
  
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::construct_, construct, 2)  
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::construct_, construct, 3)  
  NT2_FUNCTION_IMPLEMENTATION_SELF(nt2::tag::construct_, construct, 4)
}

#endif

