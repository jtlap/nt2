//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_INDEG_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_INDEG_HPP_INCLUDED

#include <nt2/include/functions/indeg.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T>
    valder<T> indeg(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      auto tmp = d_indeg(u.val);
      return valder<T>(indeg(u.val()), tmp*u.der());
    };
  }
}

#endif
