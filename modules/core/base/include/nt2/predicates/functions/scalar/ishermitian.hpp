//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_PREDICATES_FUNCTIONS_SCALAR_ISHERMITIAN_HPP_INCLUDED
#define NT2_PREDICATES_FUNCTIONS_SCALAR_ISHERMITIAN_HPP_INCLUDED

#include <nt2/predicates/functions/ishermitian.hpp>
#include <nt2/include/functions/scalar/is_real.hpp>

namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( ishermitian_, tag::cpu_
                            , (A0)
                            , (scalar_< unspecified_<A0> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&a0) const
    {
      return is_real(a0);
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( ishermitian_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< unspecified_<A0> >)
                              (scalar_< unspecified_<A1> >)
                            )
  {
    typedef bool result_type;

    BOOST_FORCEINLINE
    result_type operator()(const A0&a0, const A1&) const
    {
      return is_real(a0);
    }
  };
} }

#endif
