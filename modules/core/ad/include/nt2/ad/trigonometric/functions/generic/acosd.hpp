//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOSD_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_ACOSD_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/acosd.hpp>
#include <nt2/include/functions/d_acosd.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    valder<T> acosd(const valder<T>&u)
    {
      return valder<T>(nt2::acosd(u.val()), d_acosd(u.val())*u.der());
    };
  }
}

#endif
