//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SIND_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SIND_HPP_INCLUDED

#include <nt2/include/functions/simd/sind.hpp>
#include <nt2/include/functions/sincosd.hpp>
#include <nt2/include/constants/deginrad.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T>
    valder<T> sind(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      T s, c;
      nt2::sincosd(u.val(), s, c);
      return valder<T>(s, Deginrad<elem_t>()*c*u.der());
    };
  }
}

#endif
