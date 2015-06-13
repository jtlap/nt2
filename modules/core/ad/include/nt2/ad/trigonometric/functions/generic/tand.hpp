//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_TAND_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_TAND_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/tand.hpp>
#include <nt2/include/functions/simd/d_tand.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T>
    valder<T> tand(const valder<T>&u)
    {
      return valder<T>(nt2::tand(u.val()), d_tand(u.val())*u.der());
    };
  }
}

#endif
