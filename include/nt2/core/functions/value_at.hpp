//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_CORE_FUNCTIONS_VALUE_AT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_VALUE_AT_HPP_INCLUDED

#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    struct value_at_ {};
  }

  NT2_FUNCTION_IMPLEMENTATION(tag::value_at_, value_at, 2)
}

#include <nt2/core/functions/impl/value_at.hpp>

#endif
