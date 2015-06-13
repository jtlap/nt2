//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_ATAN2D_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_ATAN2D_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/atan2d.hpp>
#include <nt2/include/functions/simd/d_atand.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2>
    valder<T1> atan2d(const valder<T1>&u, const valder<T2>&v)
    {
      return valder<T1>(atan2d(u.val(), v.val())
                       , d_atand(v.val()/u.val())*(v/u).der());
    };
  }
}

#endif
