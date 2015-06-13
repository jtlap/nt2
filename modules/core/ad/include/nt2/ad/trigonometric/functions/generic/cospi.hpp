//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_COSPI_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_COSPI_HPP_INCLUDED

#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/sincospi.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T>
    valder<T> cospi(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      T s, c;
      nt2::sincospi(u.val(), s, c);
    return valder<T>(c, -Pi<elem_t>()*s*u.der());
    };
  }
}

#endif
