//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_COSECANT_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_COSECANT_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/cosecant.hpp>
#include <nt2/trigonometric/include/functions/simd/cotangent.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class Mode, class T> BOOST_FORCEINLINE
    valder<T> cosecant(const valder<T>&u)
    {
      auto tmp = nt2::cosecant<Mode>(u.val());
      return valder<T>(tmp, -nt2::cotangent<Mode>(u.val())*tmp*u.der());
    };
  }
}

#endif
