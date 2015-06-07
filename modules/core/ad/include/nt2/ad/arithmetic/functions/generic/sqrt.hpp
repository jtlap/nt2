//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_SQRT_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_SQRT_HPP_INCLUDED

#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    valder<T> sqrt(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      auto tmp = nt2::sqrt(u.val());
      auto tmp1 = nt2::rec(tmp);
      return valder<T>(tmp, tmp1*u.der()*Half<elem_t>());
    };
  }
}

#endif
