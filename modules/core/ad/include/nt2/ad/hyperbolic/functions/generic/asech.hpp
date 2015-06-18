//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_HYPERBOLIC_FUNCTIONS_GENERIC_ASECH_HPP_INCLUDED
#define NT2_AD_HYPERBOLIC_FUNCTIONS_GENERIC_ASECH_HPP_INCLUDED

#include <nt2/hyperbolic/include/functions/simd/asech.hpp>
#include <nt2/include/functions/simd/d_asech.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    valder<T> asech(const valder<T>&u)
    {
      return valder<T>(nt2::asech(u.val())
                      , d_asech(u.val())*u.der());
    };
  }
}

#endif
