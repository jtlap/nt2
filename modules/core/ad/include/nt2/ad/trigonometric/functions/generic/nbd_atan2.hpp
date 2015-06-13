//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_NBD_ATAN2_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_NBD_ATAN2_HPP_INCLUDED

#include <nt2/include/functions/nbd_atan2.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T>
    valder<T> nbd_atan2(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      auto tmp = d_nbd_atan2(u.val);
      return valder<T>(nbd_atan2(u.val()), tmp*u.der());
    };
  }
}

#endif
