//==============================================================================
//          Copyright 2015 J.T. Lapreste
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_SCALAR_ISHESS_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_SCALAR_ISHESS_HPP_INCLUDED

#include <nt2/predicates/functions/ishess.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( ishess_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&) const { return true; }
  };
} }

#endif
