//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_ISINSIDE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_ISINSIDE_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    struct isinside_ : ext::unspecified_<isinside_>
    {
      typedef ext::unspecified_<isinside_> parent;
    };
  }

  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isinside_, isinside, 2)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::isinside_, isinside, 3)
}

#endif
