//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_CSCPI_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_CSCPI_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/cscpi.hpp>
#include <nt2/trigonometric/include/functions/simd/cotpi.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    valder<T> cscpi(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      auto tmp = nt2::cscpi(u.val());
      return valder<T>(tmp,  -tmp*Pi<elem_t>()*nt2::cotpi(u.val())*u.der());
    };
  }
}

#endif
