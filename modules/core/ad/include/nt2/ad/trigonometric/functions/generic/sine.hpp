//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SINE_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SINE_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/sine.hpp>
#include <nt2/include/functions/sine.hpp>
#include <nt2/include/functions/sinecosine.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class Mode, class T>
    valder<T> sine(const valder<T>&u)
    {
      T s, c;
      nt2::sinecosine<Mode>(u.val(), s, c);
      return valder<T>(s, c*u.der());
    };
  }
}

#endif
