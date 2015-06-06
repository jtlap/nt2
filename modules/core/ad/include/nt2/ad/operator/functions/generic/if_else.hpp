//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IF_ELSE_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IF_ELSE_HPP_INCLUDED

#include <nt2/include/functions/if_else.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L, class T> BOOST_FORCEINLINE
    valder<T> if_else(const L & l, const valder<T>&u, const valder<T>&v)
    {
      return valder<T>(nt2::if_else(l, u.val(), v.val()), nt2::if_else(l, u.der(), v.der()));
    };
    template < class L, class T > BOOST_FORCEINLINE
    valder<T> if_else(const L&l, const T &u, const valder<T>&v)
    {
      typedef typename valder<T>::elem_t elem_t;
      valder<T> uu(u, Zero<elem_t>());
      return valder<T>(nt2::if_else(l, u, v.val()), nt2::if_else(l, uu.der(), v.der()));
    };
    template < class L, class T > BOOST_FORCEINLINE
    valder<T> if_else(const L&l, const valder<T> &u, const T&v)
    {
      typedef typename valder<T>::elem_t elem_t;
      valder<T> vv(v, Zero<elem_t>());
      return valder<T>(nt2::if_else(l, u.val(), v), nt2::if_else(l, u.der(), vv.der()));
    };
  }
}

#endif
